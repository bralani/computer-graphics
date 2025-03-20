#include "scene/TestScene.hpp"
#include "materials/Texture.hpp"
#include "materials/BasicMaterial.hpp"
#include "materials/PBRMaterial.hpp"
#include "shaders/PhongShader.hpp"
#include "shaders/PBRShader.hpp"
#include "lights/DirectionalLight.hpp"
#include "lights/PointLight.hpp"
#include "lights/SpotLight.hpp"
#include "camera/FirstPersonCamera.hpp"
#include <iostream>

// constructor
TestScene::TestScene()
{
  // create the camera
  auto camera = std::make_shared<FirstPersonCamera>(
    glm::vec3(0.0f, 1.5f, 7.0f),  // Posizione iniziale
    glm::radians(0.0f),           // Yaw iniziale (in radianti)
    glm::radians(0.0f),           // Pitch iniziale (in radianti)
    glm::radians(0.0f)            // Roll iniziale (in radianti)
);

  PBRShader shader;

  // create the models
  auto root = createRoot();
  
  const std::array<const char*, 6>& hdri_textures = {
    "assets/textures/hdri/bluecloud_ft.jpg",
    "assets/textures/hdri/bluecloud_bk.jpg",
    "assets/textures/hdri/bluecloud_up.jpg",
    "assets/textures/hdri/bluecloud_dn.jpg",
    "assets/textures/hdri/bluecloud_rt.jpg",
    "assets/textures/hdri/bluecloud_lf.jpg",
  };

  // setup the scene
  setup(root, camera, shader, hdri_textures);
}

std::shared_ptr<Object> TestScene::createRoot()
{
  std::vector<std::shared_ptr<Mesh>> meshes1, meshes2;
  std::vector<std::shared_ptr<Object>> children;
  
  Texture texture1("assets/textures/bog_albedo.png", TextureType::Diffuse);
  Texture texture2("assets/textures/bog_metallic.png", TextureType::Metallic);
  Texture texture3("assets/textures/bog_roughness.png", TextureType::Roughness);
  Texture texture4("assets/textures/bog_normal-dx.png", TextureType::Normal);
  Texture texture5("assets/textures/bog_ao.png", TextureType::AmbientOcclusion);
  PBRMaterial material1(texture1, texture3, texture2, texture4, texture5);
  
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
  auto child1 = std::make_shared<Object>();
  child1.get()->setMeshes(meshes1);
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
  auto child2 = std::make_shared<Object>();
  child2.get()->setMeshes(meshes2);
  child2.get()->transform.setPosition(glm::vec3(5.0f, 0.0f, -5.0f));
  child2.get()->transform.setScale(glm::vec3(5.0f, 2.0f, 5.0f));

  children.push_back(child1);
  children.push_back(child2);

  auto root = std::make_shared<Object>();
  root.get()->setChildrenObjects(children);

  DirectionalLight dirLight(
    glm::vec3(1.0f, 1.0f, 1.0f), 
    glm::vec3(0.1f, .9f, 1.0f),
    50.0f);

  PointLight pointLight(
    glm::vec3(1.0f, 1.0f, 1.0f), 
    glm::vec3(1.0f, 1.0f, 1.0f), 
    3.0f);

  root.get()->setLights({std::make_shared<DirectionalLight>(dirLight), std::make_shared<PointLight>(pointLight)});

  return root;
}