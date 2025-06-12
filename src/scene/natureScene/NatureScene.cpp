#include "scene/natureScene/NatureScene.hpp"
#include "scene/natureScene/object/Grounds.hpp"
#include "scene/natureScene/object/CollisionWater.hpp"
#include "scene/natureScene/object/Tree.hpp"
#include "scene/natureScene/object/Boat.hpp"
#include "scene/natureScene/object/Rocks.hpp"
#include "scene/natureScene/object/Terrain.hpp"
#include "scene/natureScene/object/Treasure.hpp"
#include "scene/natureScene/object/Homes.hpp"
#include "scene/natureScene/object/Heat.hpp"
#include "scene/natureScene/object/Carretto.hpp"
#include "materials/Texture.hpp"
#include "materials/BasicMaterial.hpp"
#include "materials/PBRMaterial.hpp"
#include "shaders/PhongShader.hpp"
#include "shaders/PBRShader.hpp"
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

	const std::array<const char *, 6> &hdri_textures = {
		"assets/textures/hdri/sun/bluecloud_ft.jpg",
		"assets/textures/hdri/sun/bluecloud_bk.jpg",
		"assets/textures/hdri/sun/bluecloud_up.jpg",
		"assets/textures/hdri/sun/bluecloud_dn.jpg",
		"assets/textures/hdri/sun/bluecloud_rt.jpg",
		"assets/textures/hdri/sun/bluecloud_lf.jpg",
	};

	const std::array<const char *, 6> &hdri_textures2 = {
		"assets/textures/hdri/moon/left.png",
		"assets/textures/hdri/moon/right.png",
		"assets/textures/hdri/moon/top.png",
		"assets/textures/hdri/moon/bottom.png",
		"assets/textures/hdri/moon/back.png",
		"assets/textures/hdri/moon/front.png",
	};

	// setup the scene
	setup(root, camera, shader, hdri_textures, hdri_textures2);
	addCollisions();
	collectBarrels(root);
}

void NatureScene::initializePhysicsWorld()
{
	auto collisionConfiguration = new btDefaultCollisionConfiguration();
	auto dispatcher = new btCollisionDispatcher(collisionConfiguration);
	auto broadphase = new btDbvtBroadphase();
	btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
	physicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, sol, collisionConfiguration);
	physicsWorld->setGravity(btVector3(0, -9.8, 0));
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
	auto collisionWater = std::make_shared<CollisionWater>();
	auto boat = std::make_shared<Boat>();
	auto tree = std::make_shared<Tree>();
	auto treasure = std::make_shared<Treasure>();
	auto homes = std::make_shared<Homes>();
	auto heat = std::make_shared<Heat>();
	auto carretto = std::make_shared<Carretto>();
	boatCamera = std::make_shared<BoatCamera>(boat);
	mulino = std::make_shared<Mulino>();	
	walls = std::make_shared<Walls>();
	torchs = std::make_shared<Torchs>();


	auto root = std::make_shared<Object>();
	root->setChildrenObjects({ground, boat, homes, carretto, mulino, walls, heat, torchs, /*rocks,*/ tree, treasure, collisionWater});

	DirectionalLight dirLight(
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(0.0f, -1.0f, .0f),
		40.0f);

	root.get()->setLights({std::make_shared<DirectionalLight>(dirLight)});

	return root;
}

void NatureScene::update()
{
	auto window = Input::getWindow();
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaT = static_cast<float>(currentTime - lastTime);
	lastTime = currentTime;

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

	bool gPressed = Input::getKey(GLFW_KEY_G);
	if (gPressed && !gDebounce) {
		gDebounce = true;

		if (!isHolding) {
			// Find nearest barrel
			glm::vec3 camPos = camera->getPosition();
			float bestDist = pickupRange;
			std::shared_ptr<BarrelMesh> nearest = nullptr;

			for (auto& b : allBarrels) {
				glm::vec3 bpos = b->transform.getPosition();
				float d = glm::distance(camPos, bpos);
				if (d < bestDist) {
					bestDist = d;
					nearest = b;
				}
				std::cout << std::endl;
			}

			if (nearest) {
				// Grab barrel
				heldBarrel = nearest;
				isHolding   = true;
			}
		}
		else {
			// Drop barrel
			glm::vec3 camPos  = camera->getPosition();
			glm::vec3 forward = camera->getFront();
			glm::vec3 dropPos = camPos + forward * dropDist;
			dropPos.y -= 1.5f;

			heldBarrel->transform.setPosition(dropPos);
			heldBarrel->transform.setScale(glm::vec3(1.0f));
			heldBarrel->transform.setRotation(glm::vec3(-7.6584f, -11.0591f, 74.6419f));
			heldBarrel->setGlobalTransform(heldBarrel->transform);

			heldBarrel = nullptr;
			isHolding  = false;
		}
	}
	else if (!gPressed) {
		gDebounce = false;
	}

	bool hPressed = Input::getKey(GLFW_KEY_H);
	if (hPressed && !hDebounce) {
		hDebounce = true;
		changeSky();
	}
	else if (!hPressed) {
		hDebounce = false;
	}


	checkChangeCamera();

	camera->update();

	if (isHolding && heldBarrel) {
		glm::vec3 camPos   = camera->getPosition();
		glm::vec3 worldUp  = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 forward  = camera->getFront();
		glm::vec3 right    = -camera->getRight();

		glm::vec3 worldOff = right * holdOffset.x
						   + worldUp	* holdOffset.y
						   + forward	* holdOffset.z;

		heldBarrel->transform.setPosition(camPos + worldOff);
		heldBarrel->transform.setScale(glm::vec3(0.2f));
		heldBarrel->transform.setRotation(glm::vec3(
			camera->getYaw(),
			camera->getPitch(),
			camera->getRoll()
		));
		heldBarrel->setGlobalTransform(heldBarrel->transform);
	}

	// update the camera and physics world
  physicsWorld->stepSimulation(deltaT, 2, 1.0f / 60.0f);
	menu->update();
	mulino->update();
	walls->update(camera->getPosition());
}

void NatureScene::checkChangeCamera() {
	bool vpressedCurrent = Input::getKey(GLFW_KEY_V);
	if (vpressedCurrent && !vPressedPrev) {
		glm::vec3 spawn1 = glm::vec3(154.169, -8.70866, 81.3701); 
		glm::vec3 spawn2 = glm::vec3(-199.512, -8.77594, -93.2629); 

		if (cameraType == 0) {

			glm::vec3 cameraPos = camera->getPosition();

			// check if the distance to the boat is small enough to switch to boat camera
			auto dist = glm::distance(cameraPos, spawn1);
			if (dist < 20.0f) {
				cameraType = 1;
				setCamera(boatCamera);
			}

			dist = glm::distance(cameraPos, spawn2);
			if (dist < 20.0f) {
				cameraType = 1;
				setCamera(boatCamera);
			}

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

void NatureScene::collectBarrels(const std::shared_ptr<Object>& node) {
	for (auto& mesh : node->getMeshes()) {
        if (auto b = std::dynamic_pointer_cast<BarrelMesh>(mesh))
            allBarrels.push_back(b);
    }
    
    for (auto& child : node->getChildrenObjects())
        collectBarrels(child);
}


void NatureScene::changeSky() {
	bool isDay = !getIsDay();
	auto sun = root->getLights()[0];

	if(isDay) {
		sun->setIntensity(40.0f);

		auto allTorchs = torchs->getChildrenObjects();
		for (const auto& torch : allTorchs) {
			auto light = torch->getLights()[0];
			light->setIntensity(0.0f);
		}

	} else {
		sun->setIntensity(2.0f);

		auto allTorchs = torchs->getChildrenObjects();
		for (const auto& torch : allTorchs) {
			auto light = torch->getLights()[0];
			light->setIntensity(30.0f);
		}
	}

	setIsDay(isDay);
}