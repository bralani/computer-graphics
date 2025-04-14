#ifndef GROUNDMESH_HPP
#define GROUNDMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/GroundMaterial.hpp"

class GroundMesh : public Mesh {
public:
    GroundMesh() : Mesh("assets/models/ground.obj") {
      
      GroundMaterial material;
      this->setMaterial(std::make_shared<GroundMaterial>(material));
      this->transform.setScale(glm::vec3(8.0f));
      this->transform.setPosition(glm::vec3(0.0f, -200.0f, 0.0f));
    }
private:
};

#endif // GROUNDMESH_HPP
