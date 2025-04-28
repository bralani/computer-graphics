#include "scene/natureScene/NatureScene.hpp"
#include "scene/natureScene/object/Grounds.hpp"
#include "scene/natureScene/object/Tree.hpp"
#include "scene/natureScene/object/Boat.hpp"
#include "scene/natureScene/object/Rocks.hpp"
#include "scene/natureScene/object/Terrain.hpp"
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
	physicsWorld->setGravity(btVector3(0, -0.1, 0));
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
	boatCamera = std::make_shared<BoatCamera>(boat);

	auto root = std::make_shared<Object>();
	root->setChildrenObjects({ground, rocks, boat, tree});

	DirectionalLight dirLight(
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(0.1f, -0.9f, .1f),
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

	static bool fPressedPrev = false;
	bool fpressedCurrent = Input::getKey(GLFW_KEY_F);
	if (!fpressedCurrent && fPressedPrev) {
		if (cameraType == 0) {
			cameraType = 1;
			setCamera(boatCamera);
		}
		else {
			cameraType = 0;
			setCamera(firstPersonCamera);
		}
	}
	fPressedPrev = fpressedCurrent;

	// update the camera and physics world
	camera->update();
    physicsWorld->stepSimulation(deltaT, 10);
}