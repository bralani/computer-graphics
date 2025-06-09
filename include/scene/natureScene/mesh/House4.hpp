#ifndef HOUSE4MESH_HPP
#define HOUSE4MESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/House2Material.hpp"

class House4Mesh : public Mesh {
public:
    House4Mesh() : Mesh("assets/models/house4.obj") {
      
      House2Material material;
      this->setMaterial(std::make_shared<House2Material>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};


#endif // HOUSE4MESH_HPP
