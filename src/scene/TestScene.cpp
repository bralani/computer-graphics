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
  std::vector<std::shared_ptr<Mesh>> meshes1, meshes2;
  std::vector<std::shared_ptr<Object>> children;

  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < 5; i++)
    {
      auto mesh = std::make_shared<Mesh>("assets/models/P" + std::to_string(j) + std::to_string(i) + ".obj");
      mesh.get()->transform.setRotation(glm::vec3(90.0f, 0.0f, 0.0f));
      meshes1.push_back(mesh);
    }
  }
  auto child1 = std::make_shared<Object>(meshes1);
  child1.get()->transform.setPosition(glm::vec3(5.0f, 0.0f, 0.0f));

  for (int j = 2; j < 3; j++)
  {
    for (int i = 0; i < 5; i++)
    {
      auto mesh = std::make_shared<Mesh>("assets/models/P" + std::to_string(j) + std::to_string(i) + ".obj");
      meshes2.push_back(mesh);
    }
  }
  auto child2 = std::make_shared<Object>(meshes2);

  children.push_back(child1);
  children.push_back(child2);

  auto root = std::make_shared<Object>(children);

  return root;
}