#ifndef HOME_MESH_HPP
#define HOME_MESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/HomeMaterial.hpp"

class HomeMesh : public Mesh {
public:
    HomeMesh() : Mesh("assets/models/home.obj") {
      
      HomeMaterial material;
      this->setMaterial(std::make_shared<HomeMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

#endif // HOME_MESH_HPP
