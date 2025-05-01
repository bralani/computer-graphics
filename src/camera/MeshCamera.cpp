#include "camera/MeshCamera.hpp"
#include "utilities/Input.hpp"

#include "camera/MeshCamera.hpp"
#include "utilities/Input.hpp"

MeshCamera::MeshCamera(const std::shared_ptr<Rocks>& meshObject)
    : Camera(glm::vec3(0.0f), 0.0f, 0.0f, 0.0f) {
    this->meshObject = meshObject;
    position = calculateCameraPos();
    distanceFromMesh = 8.0f;  // Initial follow distance
    yaw = 0.0f;
    pitch = glm::radians(20.0f);  // Initial camera angle
}


MeshCamera::~MeshCamera() {}

glm::mat4 MeshCamera::getViewMatrix() const {
    return glm::lookAt(position, followPoint, glm::vec3(0, 1, 0));
}

glm::vec3 MeshCamera::calculateCameraPos() {
    // Get mesh's forward direction from its rotation
    glm::vec3 meshRotation = meshObject->getMeshes()[0]->getGlobalTransform().getRotation();
    float meshYaw = glm::radians(meshRotation.y);
    
    // Calculate offset based on current camera angles and mesh rotation
    glm::vec3 offset(
        distanceFromMesh * sin(yaw + meshYaw) * cos(pitch),
        -distanceFromMesh * sin(pitch),
        distanceFromMesh * cos(yaw + meshYaw) * cos(pitch)
    );

    // Get mesh position and calculate follow point
    glm::vec3 meshPos = meshObject->getMeshes()[0]->getGlobalTransform().getPosition();
    followPoint = meshPos + glm::vec3(0, 1.5f, 0);  // Point slightly above mesh
    
    return followPoint - offset;
}

void MeshCamera::update() {
    auto window = Input::getWindow();
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaT = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    // input mouse-look
    int winW, winH;
    glfwGetWindowSize(window, &winW, &winH);
    double centerX = winW / 2.0, centerY = winH / 2.0;
    auto [xpos, ypos] = Input::getCursorPos();
    double dx = xpos - centerX, dy = ypos - centerY;
    glfwSetCursorPos(window, centerX, centerY);


    const float MOUSE_SENSITIVITY = 0.1f;
    yaw   -= static_cast<float>(dx) * MOUSE_SENSITIVITY * deltaT;
    pitch -= static_cast<float>(dy) * MOUSE_SENSITIVITY * deltaT;
    pitch = glm::clamp(pitch, glm::radians(10.0f), glm::radians(80.0f));

    // la rotellina aggiorna già distanceFromMesh via callback
    double yoff = Input::getScrollOffset();
    if (yoff != 0.0) {
        processMouseScroll(static_cast<float>(yoff));
    }

    // ricalcola la posizione in base a yaw, pitch e distanceFromMesh
    position = calculateCameraPos();

    meshObject->update();
}


void MeshCamera::processMouseScroll(float yoffset) {
    const float zoomSpeed = 1.0f;

    // yoffset >0 = rotella avanti = avvicina (diminuisci distanza)
    distanceFromMesh -= yoffset * zoomSpeed;

    // clamp tra 4 e 15 unità
    distanceFromMesh = glm::clamp(distanceFromMesh, 4.0f, 50.0f);
}
