#include "scene/TestScene.hpp"
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

// constructor
TestScene::TestScene()
{
	// create the camera
	auto camera = std::make_shared<FirstPersonCamera>(
		glm::vec3(0.0f, 1.5f, 7.0f), // Posizione iniziale
		glm::radians(0.0f),			 // Yaw iniziale (in radianti)
		glm::radians(0.0f),			 // Pitch iniziale (in radianti)
		glm::radians(0.0f)			 // Roll iniziale (in radianti)
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

std::shared_ptr<Object> TestScene::createRoot()
{
	std::vector<std::shared_ptr<Mesh>> meshes1, meshes2;
	std::vector<std::shared_ptr<Object>> children;

	Texture texture1("assets/textures/bog_albedo.png", TextureType::Diffuse);
	Texture texture2("assets/textures/bog_metallic.png", TextureType::Metallic);
	Texture texture3("assets/textures/bog_roughness.png", TextureType::Roughness);
	Texture texture4("assets/textures/bog_normal-dx.png", TextureType::Normal);
	Texture texture5("assets/textures/bog_ao.png", TextureType::AmbientOcclusion);
	PBRMaterial material1(texture1, texture3, texture2, texture4, texture5);

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			auto mesh = std::make_shared<Mesh>("assets/models/P" + std::to_string(j) + std::to_string(i) + ".obj");
			mesh.get()->setMaterial(std::make_shared<PBRMaterial>(material1));

			if (j == 0 && i == 0)
			{
				mesh.get()->transform.setRotation(glm::vec3(90.0f, 0.0f, 0.0f));
			}
			// mesh.get()->transform.setRotation(glm::vec3(90.0f, 0.0f, 0.0f));
			meshes1.push_back(mesh);
		}
	}
	auto child1 = std::make_shared<Object>();
	child1.get()->setMeshes(meshes1);
	child1.get()->transform.setRotation(glm::vec3(90.0f, 0.0f, 0.0f));

	for (int j = 2; j < 3; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			auto mesh = std::make_shared<Mesh>("assets/models/P" + std::to_string(j) + std::to_string(i) + ".obj");
			mesh.get()->setMaterial(std::make_shared<PBRMaterial>(material1));
			meshes2.push_back(mesh);
		}
	}

	auto mesh = std::make_shared<Mesh>("assets/models/rock.obj");
	Texture texture1_rock("assets/textures/rock_low_Base_Color.png", TextureType::Diffuse);
	Texture texture2_rock("assets/textures/rock_low_Metallic.png", TextureType::Metallic);
	Texture texture3_rock("assets/textures/bog_roughness.png", TextureType::Roughness);
	Texture texture4_rock("assets/textures/rock_low_Normal_DirectX.png", TextureType::Normal);
	Texture texture5_rock("assets/textures/rock_low_Mixed_AO.png", TextureType::AmbientOcclusion);
	PBRMaterial material2(texture1_rock, texture3_rock, texture2_rock, texture4_rock, texture5_rock);
	mesh.get()->setMaterial(std::make_shared<PBRMaterial>(material2));
	mesh.get()->transform.setScale(glm::vec3(0.1f));
	meshes2.push_back(mesh);

	auto child2 = std::make_shared<Object>();
	child2.get()->setMeshes(meshes2);
	child2.get()->transform.setPosition(glm::vec3(5.0f, 0.0f, -5.0f));
	child2.get()->transform.setScale(glm::vec3(5.0f, 2.0f, 5.0f));

	children.push_back(child1);
	children.push_back(child2);

	auto root = std::make_shared<Object>();
	root.get()->setChildrenObjects(children);

	DirectionalLight dirLight(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.1f, .9f, 1.0f),
		50.0f);

	PointLight pointLight(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		3.0f);

	root.get()->setLights({std::make_shared<DirectionalLight>(dirLight), std::make_shared<PointLight>(pointLight)});

	return root;
}

void TestScene::update()
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