#ifndef WATERMESH_HPP
#define WATERMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/WaterMaterial.hpp"

class WaterMesh : public Mesh {
public:
    WaterMesh() : Mesh("assets/models/water.obj") {
      
      WaterMaterial material;
      this->setMaterial(std::make_shared<WaterMaterial>(material));
    }
private:
};

#endif // WATERMESH_HPP
