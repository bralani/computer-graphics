#ifndef HEAT_MESH_HPP
#define HEAT_MESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/HomeMaterial.hpp"

class HeatMesh : public Mesh {
public:
    HeatMesh() : Mesh("assets/models/heat.obj") {
      
      HomeMaterial material;
      this->setMaterial(std::make_shared<HomeMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

#endif // HEAT_MESH_HPP
