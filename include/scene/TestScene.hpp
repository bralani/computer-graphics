#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include "scene/Scene.hpp"

class TestScene : public Scene {
public:
    TestScene();
    ~TestScene() = default;
private:
    std::shared_ptr<Object> createRoot();
};

#endif // TESTSCENE_HPP
