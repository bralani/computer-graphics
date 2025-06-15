#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(const glm::vec3& pos = glm::vec3(0.0f),
           float yaw = 0.0f,
           float pitch = 0.0f);
    virtual ~Camera();

    virtual void update();
    void setPosition(const glm::vec3& pos);
    void setYaw(float newYaw);
    void setPitch(float newPitch);

    const glm::vec3& getPosition() const;
    float getYaw()   const;
    float getPitch() const;

    virtual glm::vec3 getFront() const = 0;

    virtual glm::mat4 getViewMatrix() const = 0;

    glm::mat4 getProjectionMatrix() const;

    void setPerspective(float fovDeg, float aspect, float nearPlane, float farPlane);

    void setOrthographic(float left, float right,
                         float bottom, float top,
                         float nearPlane, float farPlane);

protected:
    float getWindowAspect() const;

    glm::vec3 position;
    float yaw;
    float pitch;
    glm::mat4 projection {1.0f};
};

#endif
