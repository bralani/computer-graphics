#ifndef HOUSE3MESH_HPP
#define HOUSE3MESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/House3Material.hpp"

class House3BrickMesh : public Mesh {
public:
    House3BrickMesh() : Mesh("assets/models/house3/brick.obj") {
      
      House3BrickMaterial material;
      this->setMaterial(std::make_shared<House3BrickMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

class House3ConcreteMesh : public Mesh {
public:
    House3ConcreteMesh() : Mesh("assets/models/house3/concrete.obj") {
      
      House3ConcreteMaterial material;
      this->setMaterial(std::make_shared<House3ConcreteMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

class House3RoofMesh : public Mesh {
public:
    House3RoofMesh() : Mesh("assets/models/house3/grey_roof.obj") {
      
      House3RoofMaterial material;
      this->setMaterial(std::make_shared<House3RoofMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

class House3RoughWoodMesh : public Mesh {
public:
    House3RoughWoodMesh() : Mesh("assets/models/house3/rough_wood.obj") {
      
      House3RoughWoodMaterial material;
      this->setMaterial(std::make_shared<House3RoughWoodMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

class House3SandstoneMesh : public Mesh {
public:
    House3SandstoneMesh() : Mesh("assets/models/house3/sandstone.obj") {
      
      House3SandstoneMaterial material;
      this->setMaterial(std::make_shared<House3SandstoneMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

class House3PlanksMesh : public Mesh {
public:
    House3PlanksMesh() : Mesh("assets/models/house3/wood_planks.obj") {
      
      House3PlanksMaterial material;
      this->setMaterial(std::make_shared<House3PlanksMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};
#endif // HOUSE3MESH_HPP
