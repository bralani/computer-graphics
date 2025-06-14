#ifndef BOAT_CAMERA_HPP
#define BOAT_CAMERA_HPP

#include "camera/Camera.hpp"
#include "scene/natureScene/object/Boat.hpp"

enum class ViewMode { NORMAL, ISO, DIME, TRIME };

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

    glm::vec3 getFront() const override { return glm::vec3(0.0f, 0.0f, 1.0f); }

    void switchTo(ViewMode m);

private:
    glm::vec3 calculateCameraPos();
    void applyViewMode();
    void clampDistance();

    float distanceFromBoat;
    glm::vec3 followPoint;
    float scroll = 8.0f;
    ViewMode mode { ViewMode::NORMAL };

    std::shared_ptr<Boat> boatObject;
};

#endif
