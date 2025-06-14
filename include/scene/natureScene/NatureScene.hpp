#ifndef NATURESCENE_HPP
#define NATURESCENE_HPP

#include "scene/Scene.hpp"
#include "camera/BoatCamera.hpp"
#include "lights/DirectionalLight.hpp"
#include "camera/FirstPersonCamera.hpp"
#include "scene/natureScene/object/Mulino.hpp"
#include "scene/natureScene/object/Walls.hpp"
#include "scene/natureScene/object/Torch.hpp"
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
    void collectObjects(const std::shared_ptr<Object>& node);
    void changeSky();
    void grabObject();

    std::shared_ptr<Mulino> mulino = nullptr; // Mulino object
    std::shared_ptr<Walls> walls = nullptr; // Walls object
    std::shared_ptr<Torchs> torchs = nullptr; // Torchs object

    std::shared_ptr<BoatCamera> boatCamera = nullptr; // Camera for the boat
    std::shared_ptr<FirstPersonCamera> firstPersonCamera = nullptr; // Camera for the first person
    int cameraType = 0; // 0 for first person, 1 for boat
    btDynamicsWorld* physicsWorld;

    
    // commands
    inline static bool vPressedPrev = false;
    inline static bool fPressedPrev = false;

    // gets all objects in the scene
    struct PickEntry {
        std::shared_ptr<Mesh>   mesh;   // sempre valido
        Object*                 root;   // può essere nullptr
    };
    std::vector<PickEntry> pickables;

    // pickup state
    Object*                heldRoot = nullptr;
    std::shared_ptr<Mesh>  heldMesh;    // valido solo quando heldRoot == nullptr
    bool isHolding   = false;
    bool gDebounce   = false;

    bool hDebounce   = false;

    // settings for the pickup/drop
    float pickupRange = 10.0f;    // max distance to pick up an object
    float dropDist    = 4.0f;     // distance to drop the object in front of the camera
    glm::vec3 holdOffset = {0.0f, 0.0f, -2.0f};  // offset in camera‐space

};

#endif // NATURESCENE_HPP
