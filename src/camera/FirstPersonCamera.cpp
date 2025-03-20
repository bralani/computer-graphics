#include "camera/FirstPersonCamera.hpp"

FirstPersonCamera::FirstPersonCamera(const glm::vec3 &pos, float yaw, float pitch, float roll)
    : Camera(pos, yaw, pitch, roll) {}

FirstPersonCamera::~FirstPersonCamera() {}

glm::mat4 FirstPersonCamera::getViewMatrix() const {
    return glm::rotate(glm::mat4(1.0), -getPitch(), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0), -getYaw(), glm::vec3(0, 1, 0)) * glm::translate(glm::mat4(1.0), -getPosition());
}
