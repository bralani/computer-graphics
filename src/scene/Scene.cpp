#include "scene/Scene.hpp"

void Scene::setup(std::shared_ptr<Object> root, std::shared_ptr<Camera> camera, Shader &shader) {
    this->root = root;
    this->camera = camera;
    this->shader = shader;
}

void Scene::run() {
    ApiVulkan app (this);
}