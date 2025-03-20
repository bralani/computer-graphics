#ifndef FIRST_PERSON_CAMERA_HPP
#define FIRST_PERSON_CAMERA_HPP

#include "camera/Camera.hpp"

class FirstPersonCamera : public Camera {
public:
    FirstPersonCamera(const glm::vec3& pos = glm::vec3(0.0f),
                      float yaw = 0.0f,
                      float pitch = 0.0f,
                      float roll = 0.0f);

    
    virtual ~FirstPersonCamera();


    virtual glm::mat4 getViewMatrix() const override;
};

#endif
