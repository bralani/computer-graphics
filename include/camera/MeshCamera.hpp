#ifndef MESH_CAMERA_HPP
#define MESH_CAMERA_HPP

#include "camera/Camera.hpp"
#include "scene/natureScene/object/Rocks.hpp"

class MeshCamera : public Camera {
public:

    MeshCamera(const std::shared_ptr<Rocks>& meshObject);
    
    virtual ~MeshCamera();

    virtual glm::mat4 getViewMatrix() const override;

    virtual void update() override;

    virtual void processMouseScroll(float yoffset);


private:
    glm::vec3 calculateCameraPos();
    float distanceFromMesh;
    glm::vec3 followPoint;
    float scroll = 8.0f;

    std::shared_ptr<Rocks> meshObject;
};

#endif
