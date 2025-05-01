#ifndef BOAT_CAMERA_HPP
#define BOAT_CAMERA_HPP

#include "camera/Camera.hpp"
#include "scene/natureScene/object/Boat.hpp"

class BoatCamera : public Camera {
public:

    BoatCamera(const std::shared_ptr<Boat>& boatObject);
    
    virtual ~BoatCamera();

    virtual glm::mat4 getViewMatrix() const override;

    virtual void update() override;

    virtual void processMouseScroll(float yoffset);

    glm::vec3 getBoatPosition() const {
        return boatObject->getBoatMesh()->getGlobalTransform().getPosition();
    }

private:
    glm::vec3 calculateCameraPos();
    float distanceFromBoat;
    glm::vec3 followPoint;
    float scroll = 8.0f;

    std::shared_ptr<Boat> boatObject;
};

#endif
