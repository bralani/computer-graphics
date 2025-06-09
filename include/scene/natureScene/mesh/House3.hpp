#ifndef HOUSE3MESH_HPP
#define HOUSE3MESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/House2Material.hpp"

class House3Mesh : public Mesh {
public:
    House3Mesh() : Mesh("assets/models/house3.obj") {
      
      House2Material material;
      this->setMaterial(std::make_shared<House2Material>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};


#endif // HOUSE3MESH_HPP
