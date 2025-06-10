#ifndef FIREMESH_HPP
#define FIREMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/RockMaterial.hpp"
#include "scene/natureScene/materials/TreeMaterial.hpp"

class FireRockMesh : public Mesh {
public:
    FireRockMesh() : Mesh("assets/models/fire/rocks.obj") {
      
      RockMaterial material;
      this->setMaterial(std::make_shared<RockMaterial>(material));
    }
};

class FireWoodMesh : public Mesh {
public:
    FireWoodMesh() : Mesh("assets/models/fire/wood.obj") {
      
      TreeWoodMaterial material;
      this->setMaterial(std::make_shared<TreeWoodMaterial>(material));
    }
};

#endif // FIREMESH_HPP
