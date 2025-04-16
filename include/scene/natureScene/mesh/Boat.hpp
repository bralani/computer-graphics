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
      this->transform.setPosition(glm::vec3(0.0f, 2.0f, 0.0f));
    }
private:
};

#endif // BOATMESH_HPP
