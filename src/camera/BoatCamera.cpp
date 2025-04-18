#include "camera/BoatCamera.hpp"
#include "utilities/Input.hpp"

BoatCamera::BoatCamera(const std::shared_ptr<Boat>& boatObject)
    : Camera(glm::vec3(0.0f), 0.0f, 0.0f, 0.0f) {
    this->boatObject = boatObject;
    position = calculateCameraPos();
    distanceFromBoat = 8.0f;  // Initial follow distance
    yaw = 0.0f;
    pitch = glm::radians(20.0f);  // Initial camera angle
}

BoatCamera::~BoatCamera() {}

glm::mat4 BoatCamera::getViewMatrix() const {
    return glm::lookAt(position, followPoint, glm::vec3(0, 1, 0));
}

glm::vec3 BoatCamera::calculateCameraPos() {
    // Get boat's forward direction from its rotation
    glm::vec3 boatRotation = boatObject->getBoatMesh()->getGlobalTransform().getRotation();
    float boatYaw = glm::radians(boatRotation.y);
    
    // Calculate offset based on current camera angles and boat rotation
    glm::vec3 offset(
        distanceFromBoat * sin(yaw + boatYaw) * cos(pitch),
        -distanceFromBoat * sin(pitch),
        distanceFromBoat * cos(yaw + boatYaw) * cos(pitch)
    );

    // Get boat position and calculate follow point
    glm::vec3 boatPos = boatObject->getBoatMesh()->getGlobalTransform().getPosition();
    followPoint = boatPos + glm::vec3(0, 1.5f, 0);  // Point slightly above boat
    
    return followPoint - offset;
}

void BoatCamera::update() {
    auto window = Input::getWindow();
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaT = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    // Handle window resize
    int winWidth, winHeight;
    glfwGetWindowSize(window, &winWidth, &winHeight);
    double centerX = winWidth / 2.0, centerY = winHeight / 2.0;

    // Mouse input handling
    auto [xpos, ypos] = Input::getCursorPos();
    double m_dx = xpos - centerX;
    double m_dy = ypos - centerY;
    glfwSetCursorPos(window, centerX, centerY);

    const float MOUSE_SENSITIVITY = 0.1f;
    yaw -= static_cast<float>(m_dx) * MOUSE_SENSITIVITY * deltaT;
    pitch -= static_cast<float>(m_dy) * MOUSE_SENSITIVITY * deltaT;

    // Clamp pitch to prevent flipping
    pitch = glm::clamp(pitch, glm::radians(10.0f), glm::radians(80.0f));

    if (Input::getKey(GLFW_KEY_E)) {
		scroll += 2.0f * deltaT;
	} else if (Input::getKey(GLFW_KEY_Q)) {
		scroll -= 2.0f * deltaT;
	}
	
	float zoomSpeed = 1.0f;
    distanceFromBoat = scroll * zoomSpeed;
    distanceFromBoat = glm::clamp(distanceFromBoat, 4.0f, 15.0f);

    // Update camera position
    position = calculateCameraPos();

    boatObject->update();
}