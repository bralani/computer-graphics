#ifndef FENCE_MESH_HPP
#define FENCE_MESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/HomeMaterial.hpp"

class FenceMesh : public Mesh {
public:
    FenceMesh() : Mesh("assets/models/fence.obj") {
      
      HomeMaterial material;
      this->setMaterial(std::make_shared<HomeMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

#endif // FENCE_MESH_HPP
