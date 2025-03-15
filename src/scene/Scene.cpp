#include "scene/Scene.hpp"

void Scene::setup(std::shared_ptr<Object> root, std::shared_ptr<Camera> camera, const glm::vec3& ambientLight) {
    this->root = root;
    this->camera = camera;
    this->ambientLight = ambientLight;
}

void Scene::run() {
    ApiVulkan app (this);
}