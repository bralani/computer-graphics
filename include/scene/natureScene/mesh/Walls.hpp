#ifndef WALLSMESH_HPP
#define WALLSMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/WallMaterial.hpp"
#include "scene/natureScene/materials/FabbroMaterial.hpp"

class WallMesh : public Mesh {
public:
    WallMesh() : Mesh("assets/models/walls/wall1.obj") {
      
      WallMaterial material;
      this->setMaterial(std::make_shared<WallMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

class CancelloMesh : public Mesh {
public:
    CancelloMesh() : Mesh("assets/models/walls/cancello.obj") {
      
      SpadeFabbroMaterial material;
      this->setMaterial(std::make_shared<SpadeFabbroMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

#endif // WALLSMESH_HPP
