#ifndef TERRAINMESH_HPP
#define TERRAINMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/RockMaterial.hpp"

class TerrainMesh : public Mesh {
public:
    TerrainMesh() : Mesh("assets/models/P01.obj") {
      
      RockMaterial material;
      this->setMaterial(std::make_shared<RockMaterial>(material));
    }
private:
};

#endif // TERRAINMESH_HPP
