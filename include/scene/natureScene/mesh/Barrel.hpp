#ifndef BARRELMESH_HPP
#define BARRELMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/FienileMaterial.hpp"

class BarrelMesh : public Mesh {
public:
    BarrelMesh() : Mesh("assets/models/barrel.obj") {
      
      BoardsFienileMaterial material;
      this->setMaterial(std::make_shared<BoardsFienileMaterial>(material));
    }

    const char* getDebugName() const override { return "Barrel"; }
};



#endif // BARRELMESH_HPP
