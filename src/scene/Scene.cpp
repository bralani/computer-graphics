#include "scene/Scene.hpp"

void Scene::setup(std::shared_ptr<Object> root, std::shared_ptr<Camera> camera, Shader &shader, const std::array<const char*, 6>& hdri_textures) {
    this->root = root;
    this->camera = camera;
    this->shader = shader;
    this->hdri_textures = hdri_textures;
}

void Scene::run() {
    ApiVulkan app (this);
}