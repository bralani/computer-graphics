#ifndef BOATMESH_HPP
#define BOATMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/BoatMaterial.hpp"

class BoatMesh : public Mesh {
public:
    BoatMesh() : Mesh("assets/models/boat.obj") {
      
      BoatMaterial material;
      this->setMaterial(std::make_shared<BoatMaterial>(material));
    }
private:
};

#endif // BOATMESH_HPP
