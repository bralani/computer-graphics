#ifndef HOUSE2MESH_HPP
#define HOUSE2MESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/House2Material.hpp"

class House2Mesh : public Mesh {
public:
    House2Mesh() : Mesh("assets/models/house2.obj") {
      
      House2Material material;
      this->setMaterial(std::make_shared<House2Material>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};


#endif // HOUSE2MESH_HPP
