#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include <optional>

#include "camera/Camera.hpp"
#include "objects/Object.hpp"
#include "shaders/Shader.hpp"
#include "scene/api/ApiVulkan.hpp"

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    void setup(
            std::shared_ptr<Object> root, 
            std::shared_ptr<Camera> camera, 
            Shader &shader
        );                                                      // Setup the scene
    void run();                                                 // Run the scene

    std::shared_ptr<Object> getRoot() const { return root; }    // Get the root object
    Shader getShader() const { return shader; }                 // Get the shader
    std::shared_ptr<Camera> getCamera() const { return camera; }                // Get the camera
private:
    std::shared_ptr<Object> root;                               // Root object of the scene
    std::shared_ptr<Camera> camera;                             // Camera of the scene
    Shader shader;                                              // Shader of the scene

    std::optional<ApiVulkan> app;                               // ApiVulkan
};

#endif // SCENE_HPP
