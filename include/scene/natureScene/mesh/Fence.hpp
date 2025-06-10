#ifndef FENCE_MESH_HPP
#define FENCE_MESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/House3Material.hpp"

class FenceMesh : public Mesh {
public:
    FenceMesh() : Mesh("assets/models/fence.obj") {
      
      House3RoughWoodMaterial material;
      this->setMaterial(std::make_shared<House3RoughWoodMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

#endif // FENCE_MESH_HPP
