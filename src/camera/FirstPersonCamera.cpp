#include "camera/FirstPersonCamera.hpp"
#include "utilities/Input.hpp"
#include <GLFW/glfw3.h>
#include <iomanip>

// Classe helper per il motion state
class CameraMotionState : public btMotionState {
public:
    CameraMotionState(FirstPersonCamera* cam) : m_camera(cam) {}
    
    void getWorldTransform(btTransform& worldTrans) const override {
        glm::vec3 pos = m_camera->getPosition();
        worldTrans.setOrigin(btVector3(pos.x, pos.y, pos.z));
        worldTrans.setRotation(btQuaternion(m_camera->getYaw(), 0, 0));
    }
    
    void setWorldTransform(const btTransform& worldTrans) override {
        btVector3 pos = worldTrans.getOrigin();
        m_camera->setPosition(glm::vec3(pos.x(), pos.y(), pos.z()));
    }
    
private:
    FirstPersonCamera* m_camera;
};

FirstPersonCamera::FirstPersonCamera(const glm::vec3& pos, float yaw, float pitch, float roll, btDynamicsWorld* physicsWorld)
    : Camera(pos, yaw, pitch, roll),
      m_rigidBody(nullptr),
      m_collisionShape(nullptr),
      m_motionState(nullptr),
      m_physicsWorld(physicsWorld),
      m_jumpForce(7.0f),
      m_moveForce(20.0f),
      m_maxSpeed(4.0f),
      m_worldUp(0.0f, 1.0f, 0.0f) {
    
    // Inizializzazione fisica
    m_collisionShape = new btCapsuleShape(0.5f, 4.0f);
    
    btScalar mass(1.0f);
    btVector3 localInertia(0, 0, 0);
    m_collisionShape->calculateLocalInertia(mass, localInertia);
    
    m_motionState = new CameraMotionState(this);
    
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_motionState, m_collisionShape, localInertia);
    m_rigidBody = new btRigidBody(rbInfo);
    // Configurazione rigid body
    m_rigidBody->setAngularFactor(0.0f);
    m_rigidBody->setFriction(0.8f);
    m_rigidBody->setDamping(0.0f, 0.0f);
    m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
    
    if(m_physicsWorld) {
        m_physicsWorld->addRigidBody(m_rigidBody);
    }
}

FirstPersonCamera::~FirstPersonCamera() {
    if(m_physicsWorld && m_rigidBody) {
        m_physicsWorld->removeRigidBody(m_rigidBody);
    }
    delete m_rigidBody;
    delete m_motionState;
    delete m_collisionShape;
}

void FirstPersonCamera::update() {
    auto window = Input::getWindow();
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaT = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    // Gestione input rotazione
    int winWidth, winHeight;
    glfwGetWindowSize(window, &winWidth, &winHeight);
    double centerX = winWidth / 2.0, centerY = winHeight / 2.0;
    auto [xpos, ypos] = Input::getCursorPos();
    double m_dx = xpos - centerX;
    double m_dy = ypos - centerY;

    glfwSetCursorPos(window, centerX, centerY);

    const float MOUSE_RES = 7.0f;
    glm::vec3 r;
    r.y = static_cast<float>(m_dx) / MOUSE_RES;
    r.x = static_cast<float>(m_dy) / MOUSE_RES;

    // Aggiorna rotazione
    const float ROT_SPEED = glm::radians(120.0f);
    float newYaw = this->getYaw() - ROT_SPEED * deltaT * r.y;
    float newPitch = this->getPitch() - ROT_SPEED * deltaT * r.x;
    newPitch = glm::clamp(newPitch, glm::radians(-90.0f), glm::radians(90.0f));
    this->setYaw(newYaw);
    this->setPitch(newPitch);

    // Gestione input movimento
    glm::vec3 moveDir(0.0f);
    if (Input::getKey(GLFW_KEY_A)) moveDir.x = -1.0f;
    if (Input::getKey(GLFW_KEY_D)) moveDir.x = 1.0f;
    if (Input::getKey(GLFW_KEY_S)) moveDir.z = 1.0f;
    if (Input::getKey(GLFW_KEY_W)) moveDir.z = -1.0f;

    bool shift = Input::getKey(GLFW_KEY_LEFT_SHIFT);
    float moveForce = m_moveForce;
    float maxSpeed = m_maxSpeed;
    if (shift) {
        moveForce *= 2.0f;
        maxSpeed *= 2.0f;
    }
    
    // Salto
    if (Input::getKey(GLFW_KEY_SPACE)) {
        jump();
    }

    // Calcola direzioni di movimento basate sull'orientamento
    glm::vec3 forward = glm::vec3(sin(this->getYaw()), 0, cos(this->getYaw()));
    glm::vec3 right = glm::vec3(sin(this->getYaw() + glm::half_pi<float>()), 0, cos(this->getYaw() + glm::half_pi<float>()));

    updateCameraVectors();

    // Applica forze fisiche
    if(m_rigidBody) {

        glm::vec3 desiredMove = (forward * moveDir.z + right * moveDir.x) * moveForce;
        
        // Limita velocità orizzontale
        btVector3 currentVel = m_rigidBody->getLinearVelocity();
        glm::vec3 flatVel(currentVel.x(), 0, currentVel.z());
        
        if(glm::length(flatVel) < maxSpeed) {
            m_rigidBody->applyCentralForce(btVector3(desiredMove.x, 0, desiredMove.z));
        }
    }
}

glm::mat4 FirstPersonCamera::getViewMatrix() const {
    return glm::rotate(glm::mat4(1.0), -getPitch(), glm::vec3(1, 0, 0)) * 
           glm::rotate(glm::mat4(1.0), -getYaw(), glm::vec3(0, 1, 0)) * 
           glm::translate(glm::mat4(1.0), -getPosition());
}

void FirstPersonCamera::setPositionRigidBody(const glm::vec3& pos) {
    btTransform newTransform;
    newTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
    newTransform.setRotation(btQuaternion(getYaw(), 0, 0));
    m_rigidBody->setWorldTransform(newTransform);
    m_rigidBody->getMotionState()->setWorldTransform(newTransform);
    m_rigidBody->activate();
}

void FirstPersonCamera::setPhysicsWorld(btDynamicsWorld* world) {
    if(m_physicsWorld && m_rigidBody) {
        m_physicsWorld->removeRigidBody(m_rigidBody);
    }
    
    m_physicsWorld = world;
    
    if(m_physicsWorld && m_rigidBody) {
        m_physicsWorld->addRigidBody(m_rigidBody);
    }
}

void FirstPersonCamera::jump() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    bool canJump = duration > timeJump;

    if(m_rigidBody && canJump) {
        m_rigidBody->applyCentralImpulse(btVector3(0, m_jumpForce, 0));
        timeJump = duration + 1000;             // 1 secondo di cooldown
    }
}

void FirstPersonCamera::updateCameraVectors(){
    // Calculate the new front vector
    glm::vec3 front;
    front.x = -sin(getYaw());
    front.y =  0;
    front.z = -cos(getYaw());
    m_front = glm::normalize(front);
}