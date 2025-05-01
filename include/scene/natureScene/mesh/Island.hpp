#ifndef ISLANDMESH_HPP
#define ISLANDMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/SandMaterial.hpp"

class IslandMesh : public Mesh {
public:
    IslandMesh() : Mesh("assets/models/island.obj") {
      
      SandMaterial material;
      this->setMaterial(std::make_shared<SandMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

#endif // ISLANDMESH_HPP
