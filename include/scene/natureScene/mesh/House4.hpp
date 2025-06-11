#ifndef HOUSE4MESH_HPP
#define HOUSE4MESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/House2Material.hpp"
#include "scene/natureScene/materials/House3Material.hpp"

class House4RoofMesh : public Mesh {
public:
    House4RoofMesh() : Mesh("assets/models/house4/roof.obj") {
      
      House3RoofMaterial material;
      this->setMaterial(std::make_shared<House3RoofMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

class House4WoodMesh : public Mesh {
public:
    House4WoodMesh() : Mesh("assets/models/house4/wood.obj") {
      
      House3RoughWoodMaterial material;
      this->setMaterial(std::make_shared<House3RoughWoodMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

class House4WallMesh : public Mesh {
public:
    House4WallMesh() : Mesh("assets/models/house4/wall.obj") {
      
      House3ConcreteMaterial material;
      this->setMaterial(std::make_shared<House3ConcreteMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};


#endif // HOUSE4MESH_HPP
