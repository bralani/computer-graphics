#include "scene/Scene.hpp"
#include "utilities/Input.hpp"

void Scene::setup(std::shared_ptr<Object> root, std::shared_ptr<Camera> camera, Shader &shader, const std::array<const char*, 6>& hdri_textures, const std::array<const char*, 6>& hdri_textures2) {
    this->root = root;
    this->camera = camera;
    this->shader = shader;
    this->hdri_textures = hdri_textures;
    this->hdri_textures2 = hdri_textures2;
    this->menu = std::make_shared<Menu>();
}

void Scene::run(bool compute_shadows) {
    ApiVulkan app (this, compute_shadows);
}