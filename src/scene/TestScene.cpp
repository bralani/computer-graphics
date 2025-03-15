#include "scene/TestScene.hpp"
#include <iostream>

// constructor
TestScene::TestScene()
{
  // create the camera
  auto camera = std::make_shared<Camera>();

  // create the ambient light
  glm::vec3 ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);

  // create the models
  auto root = createRoot();

  // setup the scene
  setup(root, camera, ambientLight);
}

std::shared_ptr<Object> TestScene::createRoot()
{
  std::vector<std::shared_ptr<Mesh>> meshes;

  for (int j = 0; j < 3; j++)
  {
    for (int i = 0; i < 5; i++)
    {
      auto mesh = std::make_shared<Mesh>("assets/models/P" + std::to_string(j) + std::to_string(i) + ".obj");
      meshes.push_back(mesh);
    }
  }

  auto root = std::make_shared<Object>(meshes);
  return root;
}