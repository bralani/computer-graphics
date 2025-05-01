#ifndef TREASUREMESH_HPP
#define TREASUREMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/TreasureMaterial.hpp"

class ChestMesh : public Mesh {
public:
    ChestMesh() : Mesh("assets/models/chest.obj") {
      
      TreasureMaterial material;
      this->setMaterial(std::make_shared<TreasureMaterial>(material));
    }
};

class ChestGoldMesh : public Mesh {
  public:
      ChestGoldMesh() : Mesh("assets/models/chest_gold.obj") {
        
        TreasureGoldMaterial material;
        this->setMaterial(std::make_shared<TreasureGoldMaterial>(material));
      }
  };

#endif // TREASUREMESH_HPP
