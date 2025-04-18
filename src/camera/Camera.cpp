#include "camera/Camera.hpp"
#include "utilities/Input.hpp"

Camera::Camera(const glm::vec3& pos, float yaw, float pitch, float roll)
    : position(pos), yaw(yaw), pitch(pitch), roll(roll) {}

Camera::~Camera() {}

void Camera::setPosition(const glm::vec3& pos) { 
    position = pos; 
}

void Camera::setYaw(float newYaw) { 
    yaw = newYaw; 
}

void Camera::setPitch(float newPitch) { 
    pitch = newPitch; 
}

void Camera::setRoll(float newRoll) { 
    roll = newRoll; 
}

const glm::vec3& Camera::getPosition() const { 
    return position; 
}

float Camera::getYaw() const { 
    return yaw; 
}

float Camera::getPitch() const { 
    return pitch; 
}

float Camera::getRoll() const { 
    return roll; 
}

void Camera::update() {
	auto window = Input::getWindow();
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

	const float ROT_SPEED = glm::radians(120.0f);
	const float MOVE_SPEED = 2.0f;
	float newYaw = this->getYaw() - ROT_SPEED * deltaT * r.y;
	float newPitch = this->getPitch() - ROT_SPEED * deltaT * r.x;

	newPitch = glm::clamp(newPitch, glm::radians(-90.0f), glm::radians(90.0f));

	glm::vec3 currentPos = this->getPosition();

	glm::vec3 ux = glm::rotate(glm::mat4(1.0f), newYaw, glm::vec3(0, 1, 0)) * glm::vec4(1, 0, 0, 1);
	glm::vec3 uz = glm::rotate(glm::mat4(1.0f), newYaw, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1);
	glm::vec3 newPos = currentPos + MOVE_SPEED * deltaT * (m.x * ux + m.y * glm::vec3(0, 1, 0) + m.z * uz);

	this->setYaw(newYaw);
	this->setPitch(newPitch);
	this->setPosition(newPos);
}