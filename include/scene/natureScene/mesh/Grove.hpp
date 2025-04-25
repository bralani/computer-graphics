#ifndef GROVEMESH_HPP
#define GROVEMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/GroveMaterial.hpp"

class GroveMesh : public Mesh {
public:
    GroveMesh() : Mesh("assets/models/grove.obj") {
      
      GroveMaterial material;
      this->setMaterial(std::make_shared<GroveMaterial>(material));
    }
private:
};

#endif // GROVEMESH_HPP
