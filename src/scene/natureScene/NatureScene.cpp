#include "scene/natureScene/NatureScene.hpp"
#include "scene/natureScene/object/Grounds.hpp"
#include "scene/natureScene/object/Tree.hpp"
#include "scene/natureScene/object/Boat.hpp"
#include "scene/natureScene/object/Rocks.hpp"
#include "scene/natureScene/object/Terrain.hpp"
#include "scene/natureScene/object/Treasure.hpp"
#include "materials/Texture.hpp"
#include "materials/BasicMaterial.hpp"
#include "materials/PBRMaterial.hpp"
#include "shaders/PhongShader.hpp"
#include "shaders/PBRShader.hpp"
#include "lights/DirectionalLight.hpp"
#include "lights/PointLight.hpp"
#include "lights/SpotLight.hpp"
#include "camera/FirstPersonCamera.hpp"
#include "camera/BoatCamera.hpp"
#include "utilities/Input.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
#include "scene/natureScene/mesh/Ground.hpp"

// constructor
NatureScene::NatureScene()
{
	glm::vec3 position = glm::vec3(5.0f, 1.0f, 7.0f);
	glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::normalize(target - position);
	float yaw = atan2(direction.z, direction.x);
	float pitch = asin(direction.y);
	float roll = 0.0f;

	initializePhysicsWorld();

	// create the camera
	auto camera = std::make_shared<FirstPersonCamera>(
		position, // Posizione iniziale
		yaw,			 // Yaw iniziale (in radianti)
		pitch,			 // Pitch iniziale (in radianti)
		roll,			 // Roll iniziale (in radianti)
		physicsWorld 	 // Passa il mondo fisico alla camera
	);
	firstPersonCamera = camera;

	PBRShader shader;

	// create the models
	auto root = createRoot();

	// set items found to false
	itemsFound.resize(4, false);

	const std::array<const char *, 6> &hdri_textures = {
		"assets/textures/hdri/bluecloud_ft.jpg",
		"assets/textures/hdri/bluecloud_bk.jpg",
		"assets/textures/hdri/bluecloud_up.jpg",
		"assets/textures/hdri/bluecloud_dn.jpg",
		"assets/textures/hdri/bluecloud_rt.jpg",
		"assets/textures/hdri/bluecloud_lf.jpg",
	};

	// setup the scene
	setup(root, camera, shader, hdri_textures);
	addCollisions();
}

void NatureScene::initializePhysicsWorld()
{
	auto collisionConfiguration = new btDefaultCollisionConfiguration();
	auto dispatcher = new btCollisionDispatcher(collisionConfiguration);
	auto broadphase = new btDbvtBroadphase();
	btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
	physicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, sol, collisionConfiguration);
	physicsWorld->setGravity(btVector3(0, -0.05, 0));
}

void NatureScene::addCollisions()
{
	// Iterate over root's children and add collisions to each mesh
	for (const auto& child : root->getRecursiveMeshesTransform())
	{
		auto collision = child->getCollision();
		if (collision && collision->isActiveCollision())
		{
			physicsWorld->addRigidBody(collision->getRigidBody());
		}
	}
	
	// Iterate over root's children and add collisions to each mesh
	for (const auto& child : root->getRecursiveMeshesTransform())
	{
		child->setCollisionTransform();
	}
}

std::shared_ptr<Object> NatureScene::createRoot()
{
	auto rocks = std::make_shared<Rocks>();
	auto ground = std::make_shared<Grounds>();
	auto boat = std::make_shared<Boat>();
	auto tree = std::make_shared<Tree>();
	auto treasure = std::make_shared<Treasure>();
	boatCamera = std::make_shared<BoatCamera>(boat);
	meshCamera = std::make_shared<MeshCamera>(rocks);

	auto root = std::make_shared<Object>();
	root->setChildrenObjects({ground, rocks, boat, tree, treasure});

	DirectionalLight dirLight(
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(0.0f, -1.0f, .0f),
		50.0f);

	PointLight pointLight(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		3.0f);

	root.get()->setLights({std::make_shared<DirectionalLight>(dirLight)});

	return root;
}

void NatureScene::update()
{
	auto window = Input::getWindow();
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaT = static_cast<float>(currentTime - lastTime);

	static bool isPaused = false;
	static bool pDebounce = false;
	if (Input::getKey(GLFW_KEY_ESCAPE))
	{
		if (!pDebounce)
		{
			pDebounce = true;
			isPaused = !isPaused;
			if (isPaused)
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				int winWidth, winHeight;
				glfwGetWindowSize(window, &winWidth, &winHeight);
				glfwSetCursorPos(window, winWidth / 2.0, winHeight / 2.0);
			}
		}
	}
	else
	{
		pDebounce = false;
	}
	if (isPaused)
		return;

	checkChangeCamera();
	checkPickItem();

	// update the camera and physics world
	camera->update();
    physicsWorld->stepSimulation(deltaT, 10);
	menu->update();
}

void NatureScene::checkChangeCamera() {
	bool vpressedCurrent = Input::getKey(GLFW_KEY_V);
	if (vpressedCurrent && !vPressedPrev) {
		glm::vec3 spawn1 = glm::vec3(137.79, -5.71614, 24.1367); 
		glm::vec3 spawn2 = glm::vec3(-199.512, -8.77594, -93.2629); 

		if (cameraType == 0) {

			glm::vec3 cameraPos = camera->getPosition();

			// check if the distance to the boat is small enough to switch to boat camera
			auto dist = glm::distance(cameraPos, spawn1);
			if (dist < 20.0f) {
				// check if all items are found
				bool allFound = true;
				for (const auto& found : itemsFound) {
					if (!found) {
						allFound = false;
						break;
					}
				}

				if(!allFound) {
					menu->pushMenuItem(MenuItem::BoatBroken, 7.0f);
					return;
				}

				cameraType = 1;
				setCamera(boatCamera);
			}

			dist = glm::distance(cameraPos, spawn2);
			if (dist < 20.0f) {
				cameraType = 1;
				setCamera(boatCamera);
			}

		}
		else if (cameraType == 1) {
			cameraType = 2;
			setCamera(meshCamera);
		} else {
			glm::vec3 cameraPos = boatCamera->getBoatPosition();
			auto dist = glm::distance(cameraPos, spawn1);

			if (dist < 40.0f) {
				cameraType = 0;
				firstPersonCamera->setPositionRigidBody(spawn1);
				setCamera(firstPersonCamera);
			}

			dist = glm::distance(cameraPos, spawn2);
			if (dist < 40.0f) {
				cameraType = 0;
				firstPersonCamera->setPositionRigidBody(spawn2);
				setCamera(firstPersonCamera);
			}
		}
	}
	vPressedPrev = vpressedCurrent;
}

void NatureScene::checkPickItem() {
	if (cameraType != 0) return; // Only allow picking items in first person mode

	static std::vector<Transform> posItems = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 0.0f, 0.0f),
		glm::vec3(3.0f, 0.0f, 0.0f)
	};
	static float pickDistance = 5.0f; // Distance to pick items
	bool fpressedCurrent = Input::getKey(GLFW_KEY_F);
	if (fpressedCurrent && !fPressedPrev) {
		glm::vec3 cameraPos = camera->getPosition();

		for (size_t i = 0; i < posItems.size(); ++i) {
			if (itemsFound[i]) continue; // Skip if already found

			auto dist = glm::distance(cameraPos, posItems[i].getPosition());

			if (dist < pickDistance) {
				itemsFound[i] = true;

				int countItems = 0;
				for (const auto& found : itemsFound) {
					if (found) {
						countItems++;
					}
				}

				switch (countItems)
				{
					case 1:
						menu->setMenuItem(MenuItem::OneItem, 0);
						break;
					case 2:
						menu->setMenuItem(MenuItem::TwoItems, 0);
						break;
					case 3:
						menu->setMenuItem(MenuItem::ThreeItems, 0);
						break;
					case 4:
						menu->setMenuItem(MenuItem::FourItems, 0);
						break;
					
					default:
						menu->setMenuItem(MenuItem::ZeroItems, 0);
						break;
				}
			}
		}
	}
	fPressedPrev = fpressedCurrent;
}