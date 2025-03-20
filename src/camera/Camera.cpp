#include "camera/Camera.hpp"

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