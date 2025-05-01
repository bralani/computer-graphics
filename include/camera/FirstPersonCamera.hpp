#ifndef FIRST_PERSON_CAMERA_HPP
#define FIRST_PERSON_CAMERA_HPP

#include "camera/Camera.hpp"
#include <btBulletDynamicsCommon.h>

class FirstPersonCamera : public Camera {
public:
    FirstPersonCamera(const glm::vec3& pos = glm::vec3(0.0f),
                     float yaw = 0.0f,
                     float pitch = 0.0f,
                     float roll = 0.0f,
                     btDynamicsWorld* physicsWorld = nullptr);
    
    virtual ~FirstPersonCamera();

    virtual void update() override;
    virtual glm::mat4 getViewMatrix() const override;

    // Metodi per la fisica
    void setPhysicsWorld(btDynamicsWorld* world);
    void setPositionRigidBody(const glm::vec3& pos);
    btRigidBody* getRigidBody() const { return m_rigidBody; }
    void jump();

private:
    // Variabili per la fisica
    btRigidBody* m_rigidBody;
    btCollisionShape* m_collisionShape;
    btMotionState* m_motionState;
    btDynamicsWorld* m_physicsWorld;
    
    float m_jumpForce;
    float m_moveForce;
    float m_maxSpeed;
};

#endif