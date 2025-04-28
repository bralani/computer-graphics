#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <string>
#include "objects/Transform.hpp"
#include <btBulletDynamicsCommon.h>

class Collision {
public:
    Collision() = default;
    ~Collision();
    Collision(const std::string& filename, const Transform& globalTransform);
    
    bool isActiveCollision() const { return isActive; }
    void setActive(bool active) { isActive = active; }

    void setGlobalTransform(Transform& transform);
    Transform& getGlobalTransform() const { return *globalTransform; }

    btRigidBody* getRigidBody() const { return rigidBody; }

private:
    void loadObjMesh(const std::string& filename);
    void createRigidBody();

    std::shared_ptr<Transform> globalTransform;
    bool isActive = false;
    
    // Bullet Physics members
    btTriangleMesh* triangleMesh = nullptr;
    btBvhTriangleMeshShape* collisionShape = nullptr;
    btRigidBody* rigidBody = nullptr;
    btDefaultMotionState* motionState = nullptr;
    
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
};

#endif // COLLISION_HPP