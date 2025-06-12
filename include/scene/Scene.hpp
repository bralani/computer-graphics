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
#include "scene/Menu.hpp"

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    void setup(
            std::shared_ptr<Object> root, std::shared_ptr<Camera> camera, Shader &shader, const std::array<const char*, 6>& hdri_textures, const std::array<const char*, 6>& hdri_textures2
        );                                                                          // Setup the scene
    void run(bool compute_shadows);                                                 // Run the scene

    std::shared_ptr<Object> getRoot() const { return root; }                        // Get the root object
    Shader getShader() const { return shader; }                                     // Get the shader
    std::shared_ptr<Camera> getCamera() const { return camera; }                    // Get the camera
    void setCamera(std::shared_ptr<Camera> camera) { this->camera = camera; }       // Set the camera
    const std::array<const char*, 6>& getHDRI() const { return hdri_textures; }     // Get the HDRI textures
    const std::array<const char*, 6>& getHDRI2() const { return hdri_textures2; }     // Get the HDRI textures
    const std::shared_ptr<Menu> getMenu() const { return menu; }                   // Get the menu
    bool getIsDay() const { return isDay; }                                         // Get the day/night state
    void setIsDay(bool isDay) { this->isDay = isDay; }                              // Set the day/night state
    virtual void update() = 0;                                                      // Update the scene
protected:
    std::shared_ptr<Object> root;                               // Root object of the scene
    std::shared_ptr<Camera> camera;                             // Camera of the scene
    Shader shader;                                              // Shader of the scene
    std::array<const char*, 6> hdri_textures;                   // HDRI textures
    std::array<const char*, 6> hdri_textures2;                   // HDRI textures
    std::shared_ptr<Menu> menu;
    bool isDay = true;                                          

    std::optional<ApiVulkan> app;                               // ApiVulkan
};

#endif // SCENE_HPP
