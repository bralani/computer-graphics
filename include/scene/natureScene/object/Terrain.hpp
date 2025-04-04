#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Terrain.hpp"

class Terrain : public Object
{
public:
  Terrain() : Object()
  {
    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    RockMaterial material1;

    
    for (int j = 0; j < 3; j++)
    {
      for (int i = 0; i < 4; i++)
      {
        auto mesh = std::make_shared<Mesh>("assets/models/P" + std::to_string(j) + std::to_string(i) + ".obj");
        mesh.get()->setMaterial(std::make_shared<RockMaterial>(material1));

        if (j == 0 && i == 0)
        {
          mesh.get()->transform.setPosition(glm::vec3(2.0f, 0.0f, 1.0f));
          mesh.get()->transform.setRotation(glm::vec3(90.0f, 0.0f, 0.0f));
        }
        meshes.push_back(mesh);
      }
    }

    this->setMeshes(meshes);
  }

};

#endif // TERRAIN_HPP