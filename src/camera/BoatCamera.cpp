#include "camera/BoatCamera.hpp"
#include "utilities/Input.hpp"

BoatCamera::BoatCamera(const std::shared_ptr<Boat>& boatObject)
    : Camera(glm::vec3(0.0f), 0.0f, 0.0f) {
    this->boatObject = boatObject;
    position = calculateCameraPos();
    distanceFromBoat = 8.0f;  // Initial follow distance
    yaw = 0.0f;
    pitch = glm::radians(20.0f);  // Initial camera angle
    switchTo(ViewMode::NORMAL);
}

BoatCamera::~BoatCamera() {}

void BoatCamera::switchTo(ViewMode m) {
    if (mode == m) return;
    mode = m;
    applyViewMode();
}

void BoatCamera::applyViewMode() {
    float asp = getWindowAspect();
    switch (mode) {
        case ViewMode::NORMAL: {            // classic third-person view
            setPerspective(60.0f, asp, 0.1f, 500.0f);
            distanceFromBoat = 8.0f;
            break;
        }
        case ViewMode::ISO: {
            setOrthographic(-20, 20, -20, 20, -100, 100);
            pitch = glm::radians(35.264f);
            yaw   = glm::radians(45.0f);
            distanceFromBoat = 40.0f;
            break;
        }
        case ViewMode::DIME: {
            setOrthographic(-20, 20, -20, 20, -100, 100);
            pitch = glm::radians(45.0f);
            yaw   = glm::radians(45.0f);
            distanceFromBoat = 40.0f;
            break;
        }
        case ViewMode::TRIME: {
            setOrthographic(-20, 20, -20, 20, -100, 100);
            pitch = glm::radians(15.0f);
            yaw   = glm::radians(60.0f);
            distanceFromBoat = 40.0f;
            break;
        }
    }
}

glm::mat4 BoatCamera::getViewMatrix() const {
    return glm::lookAt(position, followPoint, glm::vec3(0, 1, 0));
}

glm::vec3 BoatCamera::calculateCameraPos() {
    
    // Calculate offset based on current camera angles and boat rotation
    glm::vec3 offset(
        distanceFromBoat * sin(yaw) * cos(pitch),
        -distanceFromBoat * sin(pitch),
        distanceFromBoat * cos(yaw) * cos(pitch)
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
    
    float yawOffset   = static_cast<float>(m_dx) * MOUSE_SENSITIVITY * deltaT;
    float pitchOffset = static_cast<float>(m_dy) * MOUSE_SENSITIVITY * deltaT;

    if (mode == ViewMode::NORMAL) {
        yaw   -= yawOffset;
        pitch -= pitchOffset;
        pitch = glm::clamp(pitch, glm::radians(10.0f), glm::radians(80.0f));
    }

	double yoff = Input::getScrollOffset();
    if (yoff != 0.0) {
        processMouseScroll(static_cast<float>(yoff));
    }

    bool one   = Input::getKey(GLFW_KEY_1);
    bool two   = Input::getKey(GLFW_KEY_2);
    bool three = Input::getKey(GLFW_KEY_3);
    bool zero  = Input::getKey(GLFW_KEY_0);

    static bool debounce = false;
    if (!debounce && (one || two || three || zero)) {
        if (one)   switchTo(ViewMode::ISO);
        if (two)   switchTo(ViewMode::DIME);
        if (three) switchTo(ViewMode::TRIME);
        if (zero)  switchTo(ViewMode::NORMAL);
        debounce = true;
    }
    if (!one && !two && !three && !zero) debounce = false;

    clampDistance();

    // Update camera position
    position = calculateCameraPos();

    boatObject->update();
}

void BoatCamera::processMouseScroll(float yoffset) {
    const float zoomSpeed = 1.0f;

    distanceFromBoat -= yoffset * zoomSpeed;

    distanceFromBoat = glm::clamp(distanceFromBoat, 4.0f, 50.0f);
}

void BoatCamera::clampDistance() {
    if (mode == ViewMode::NORMAL)
        distanceFromBoat = glm::clamp(distanceFromBoat, 4.0f, 20.0f);
    else
        distanceFromBoat = glm::clamp(distanceFromBoat, 20.0f, 60.0f);
}