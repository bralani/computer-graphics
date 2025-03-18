#include "scene/TestScene.hpp"
#include "materials/Texture.hpp"
#include "materials/BasicMaterial.hpp"
#include "materials/PBRMaterial.hpp"
#include "shaders/PhongShader.hpp"
#include "shaders/PBRShader.hpp"
#include <iostream>

// constructor
TestScene::TestScene()
{
  // create the camera
  auto camera = std::make_shared<Camera>();

  PBRShader shader;

  // create the models
  auto root = createRoot();

  // setup the scene
  setup(root, camera, shader);
}

std::shared_ptr<Object> TestScene::createRoot()
{
  std::vector<std::shared_ptr<Mesh>> meshes1, meshes2;
  std::vector<std::shared_ptr<Object>> children;
  
  Texture texture1("assets/textures/Picasso.jpg", TextureType::Diffuse);
  Texture texture2("assets/textures/Picasso.jpg", TextureType::Metallic);
  Texture texture3("assets/textures/Picasso.jpg", TextureType::Roughness);
  PBRMaterial material1(texture1, texture3, texture2);
  
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < 5; i++)
    {
      auto mesh = std::make_shared<Mesh>("assets/models/P" + std::to_string(j) + std::to_string(i) + ".obj");
      mesh.get()->setMaterial(material1);

      if(j==0 && i==0) {
        mesh.get()->transform.setRotation(glm::vec3(90.0f, 0.0f, 0.0f));
      }
      //mesh.get()->transform.setRotation(glm::vec3(90.0f, 0.0f, 0.0f));
      meshes1.push_back(mesh);
    }
  }
  auto child1 = std::make_shared<Object>(meshes1);
  child1.get()->transform.setRotation(glm::vec3(90.0f, 0.0f, 0.0f));

  for (int j = 2; j < 3; j++)
  {
    for (int i = 0; i < 5; i++)
    {
      auto mesh = std::make_shared<Mesh>("assets/models/P" + std::to_string(j) + std::to_string(i) + ".obj");
      mesh.get()->setMaterial(material1);
      meshes2.push_back(mesh);
    }
  }
  auto child2 = std::make_shared<Object>(meshes2);
  child2.get()->transform.setScale(glm::vec3(1.0f, 2.0f, 1.0f));

  children.push_back(child1);
  children.push_back(child2);

  auto root = std::make_shared<Object>(children);

  return root;
}