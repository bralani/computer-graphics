#ifndef NATURESCENE_HPP
#define NATURESCENE_HPP

#include "scene/Scene.hpp"
#include "camera/BoatCamera.hpp"
#include "camera/FirstPersonCamera.hpp"
#include <btBulletDynamicsCommon.h>

class NatureScene : public Scene {
public:
    NatureScene();
    ~NatureScene() = default;
private:
    std::shared_ptr<Object> createRoot();
    void initializePhysicsWorld();
    void addCollisions();
    void checkPickItem();
    void checkChangeCamera();
    void update() override;

    std::vector<bool> itemsFound;
    std::shared_ptr<BoatCamera> boatCamera = nullptr; // Camera for the boat
    std::shared_ptr<FirstPersonCamera> firstPersonCamera = nullptr; // Camera for the first person
    int cameraType = 0; // 0 for first person, 1 for boat
    btDynamicsWorld* physicsWorld;

    
    // commands
    inline static bool vPressedPrev = false;
    inline static bool fPressedPrev = false;
};

#endif // NATURESCENE_HPP
