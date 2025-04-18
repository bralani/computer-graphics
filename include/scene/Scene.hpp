#ifndef SCENE_HPP
#define SCENE_HPP

#include <array>
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
            Shader &shader,
            const std::array<const char*, 6>& hdri_textures
        );                                                                          // Setup the scene
    void run(bool compute_shadows);                                                 // Run the scene

    std::shared_ptr<Object> getRoot() const { return root; }                        // Get the root object
    Shader getShader() const { return shader; }                                     // Get the shader
    std::shared_ptr<Camera> getCamera() const { return camera; }                    // Get the camera
    const std::array<const char*, 6>& getHDRI() const { return hdri_textures; }     // Get the HDRI textures
    virtual void update() = 0;                                                      // Update the scene
protected:
    std::shared_ptr<Object> root;                               // Root object of the scene
    std::shared_ptr<Camera> camera;                             // Camera of the scene
    Shader shader;                                              // Shader of the scene
    std::array<const char*, 6> hdri_textures;                   // HDRI textures

    std::optional<ApiVulkan> app;                               // ApiVulkan
};

#endif // SCENE_HPP
