#ifndef NATURESCENE_HPP
#define NATURESCENE_HPP

#include "scene/Scene.hpp"
#include "camera/BoatCamera.hpp"
#include "lights/DirectionalLight.hpp"
#include "camera/FirstPersonCamera.hpp"
#include "scene/natureScene/object/Mulino.hpp"
#include <btBulletDynamicsCommon.h>
#include "scene/natureScene/mesh/Barrel.hpp"

class NatureScene : public Scene {
public:
    NatureScene();
    ~NatureScene() = default;
private:
    std::shared_ptr<Object> createRoot();
    void initializePhysicsWorld();
    void addCollisions();
    void checkChangeCamera();
    void update() override;
    void collectBarrels(const std::shared_ptr<Object>& node);

    std::shared_ptr<Mulino> mulino = nullptr; // Mulino object
    std::shared_ptr<BoatCamera> boatCamera = nullptr; // Camera for the boat
    std::shared_ptr<FirstPersonCamera> firstPersonCamera = nullptr; // Camera for the first person
    int cameraType = 0; // 0 for first person, 1 for boat
    btDynamicsWorld* physicsWorld;

    
    // commands
    inline static bool vPressedPrev = false;
    inline static bool fPressedPrev = false;

    // gets all barrels in the scene
    std::vector<std::shared_ptr<BarrelMesh>> allBarrels;

    // pickup state
    std::shared_ptr<BarrelMesh> heldBarrel = nullptr;
    bool isHolding   = false;
    bool gDebounce   = false;

    // settings for the pickup/drop
    float pickupRange = 10.0f;    // max distance to pick up a barrel
    float dropDist    = 1.5f;     // distance to drop the barrel in front of the camera
    glm::vec3 holdOffset = {0.1f, 0.0f, 1.0f};  // offset in camera‐space

};

#endif // NATURESCENE_HPP
