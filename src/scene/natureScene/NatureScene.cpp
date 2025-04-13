#include "scene/natureScene/NatureScene.hpp"
#include "scene/natureScene/object/Grounds.hpp"
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


	// create the camera
	auto camera = std::make_shared<FirstPersonCamera>(
		position, // Posizione iniziale
		yaw,			 // Yaw iniziale (in radianti)
		pitch,			 // Pitch iniziale (in radianti)
		roll			 // Roll iniziale (in radianti)
	);

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
}

std::shared_ptr<Object> NatureScene::createRoot()
{
	auto rocks = std::make_shared<Rocks>();
	auto terrain = std::make_shared<Terrain>();
	auto ground = std::make_shared<Grounds>();

	auto root = std::make_shared<Object>();
	root->setChildrenObjects({rocks, terrain, ground});

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

	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaT = static_cast<float>(currentTime - lastTime);
	lastTime = currentTime;

	int winWidth, winHeight;
	glfwGetWindowSize(window, &winWidth, &winHeight);
	double centerX = winWidth / 2.0, centerY = winHeight / 2.0;
	auto [xpos, ypos] = Input::getCursorPos();
	double m_dx = xpos - centerX;
	double m_dy = ypos - centerY;

	glfwSetCursorPos(window, centerX, centerY);

	const float MOUSE_RES = 7.0f;
	glm::vec3 r;
	r.y = static_cast<float>(m_dx) / MOUSE_RES;
	r.x = static_cast<float>(m_dy) / MOUSE_RES;

	if (Input::getKey(GLFW_KEY_LEFT))
		r.y = -1.0f;
	if (Input::getKey(GLFW_KEY_RIGHT))
		r.y = 1.0f;
	if (Input::getKey(GLFW_KEY_UP))
		r.x = -1.0f;
	if (Input::getKey(GLFW_KEY_DOWN))
		r.x = 1.0f;
	if (Input::getKey(GLFW_KEY_Q))
		r.z = 1.0f;
	if (Input::getKey(GLFW_KEY_E))
		r.z = -1.0f;

	glm::vec3 m(0.0f);
	if (Input::getKey(GLFW_KEY_A))
		m.x = -2.0f;
	if (Input::getKey(GLFW_KEY_D))
		m.x = 2.0f;
	if (Input::getKey(GLFW_KEY_S))
		m.z = -2.0f;
	if (Input::getKey(GLFW_KEY_W))
		m.z = 2.0f;
	if (Input::getKey(GLFW_KEY_SPACE))
		m.y = 1.0f;
	if (Input::getKey(GLFW_KEY_LEFT_SHIFT))
		m.y = -1.0f;

	if (Input::getKey(GLFW_KEY_P))
		glfwSetWindowShouldClose(window, GL_TRUE);

	auto cam = getCamera();
	const float ROT_SPEED = glm::radians(120.0f);
	const float MOVE_SPEED = 2.0f;
	float newYaw = cam->getYaw() - ROT_SPEED * deltaT * r.y;
	float newPitch = cam->getPitch() - ROT_SPEED * deltaT * r.x;

	newPitch = glm::clamp(newPitch, glm::radians(-90.0f), glm::radians(90.0f));

	glm::vec3 currentPos = cam->getPosition();

	glm::vec3 ux = glm::rotate(glm::mat4(1.0f), newYaw, glm::vec3(0, 1, 0)) * glm::vec4(1, 0, 0, 1);
	glm::vec3 uz = glm::rotate(glm::mat4(1.0f), newYaw, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1);
	glm::vec3 newPos = currentPos + MOVE_SPEED * deltaT * (m.x * ux + m.y * glm::vec3(0, 1, 0) + m.z * uz);

	cam->setYaw(newYaw);
	cam->setPitch(newPitch);
	cam->setPosition(newPos);
}