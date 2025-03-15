#include "scene/Scene.hpp"

void Scene::setup(std::vector<std::shared_ptr<Object>> models, std::shared_ptr<Camera> camera, const glm::vec3& ambientLight) {
    this->models = models;
    this->camera = camera;
    this->ambientLight = ambientLight;
}

void Scene::run() {
    ApiVulkan app (this);
}