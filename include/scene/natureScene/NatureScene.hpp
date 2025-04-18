#ifndef NATURESCENE_HPP
#define NATURESCENE_HPP

#include "scene/Scene.hpp"
#include "camera/BoatCamera.hpp"

class NatureScene : public Scene {
public:
    NatureScene();
    ~NatureScene() = default;
private:
    std::shared_ptr<Object> createRoot();
    void update() override;

    std::shared_ptr<BoatCamera> boatCamera = nullptr; // Camera for the boat
};

#endif // NATURESCENE_HPP
