#ifndef ROCKMESH_HPP
#define ROCKMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/RockMaterial.hpp"

class RockMesh : public Mesh {
public:
    RockMesh() : Mesh("assets/models/rock.obj") {
      
      RockMaterial material;
      this->setMaterial(std::make_shared<RockMaterial>(material));
      this->transform.setScale(glm::vec3(0.1f));
    }
private:
};

#endif // ROCKMESH_HPP
