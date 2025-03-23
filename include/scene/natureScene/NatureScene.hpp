#ifndef NATURESCENE_HPP
#define NATURESCENE_HPP

#include "scene/Scene.hpp"

class NatureScene : public Scene {
public:
    NatureScene();
    ~NatureScene() = default;
private:
    std::shared_ptr<Object> createRoot();
    void update() override;
};

#endif // NATURESCENE_HPP
