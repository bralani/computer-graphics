#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>

#include "camera/Camera.hpp"
#include "objects/Object.hpp"
#include "api/ApiVulkan.hpp"

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    // Add a model to the scene
    /*void addModel(std::shared_ptr<Model> model);

    // Set the scene's camera
    void setCamera(std::shared_ptr<Camera> camera);

    // Return the list of models in the scene
    const std::vector<std::shared_ptr<Model>>& getModels() const;*/

private:
    /*std::vector<std::shared_ptr<Object>> models;          // List of models in the scene
    std::shared_ptr<Camera> camera;                         // Camera of the scene
    glm::vec3 ambientLight;                                 // Global ambient light color*/

    ApiVulkan app;                                          // ApiVulkan
};

#endif // SCENE_HPP
