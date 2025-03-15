#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include <optional>

#include "camera/Camera.hpp"
#include "objects/Object.hpp"
#include "scene/api/ApiVulkan.hpp"

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    void setup(std::shared_ptr<Object> root, std::shared_ptr<Camera> camera, const glm::vec3& ambientLight);
    void run();                                                 // Run the scene

    std::shared_ptr<Object> getRoot() const { return root; }    // Get the root object
private:
    std::shared_ptr<Object> root;                               // Root object of the scene
    std::shared_ptr<Camera> camera;                             // Camera of the scene
    glm::vec3 ambientLight;                                     // Global ambient light color

    std::optional<ApiVulkan> app;                               // ApiVulkan
};

#endif // SCENE_HPP
