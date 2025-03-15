#include "scene/TestScene.hpp"

// constructor
TestScene::TestScene()
{
  // create the camera
  auto camera = std::make_shared<Camera>();

  // create the ambient light
  glm::vec3 ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);

  // create the models
  std::vector<std::shared_ptr<Object>> models;

  // setup the scene
  setup(models, camera, ambientLight);
}