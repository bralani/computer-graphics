#ifndef POZZOMESH_HPP
#define POZZOMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/PozzoMaterial.hpp"
#include "scene/natureScene/materials/CarrettoMaterial.hpp"
#include "scene/natureScene/materials/WaterMaterial.hpp"

class MurettoPozzoMesh : public Mesh {
public:
    MurettoPozzoMesh() : Mesh("assets/models/pozzo/muretto.obj") {
      
      MurettoPozzoMaterial material;
      this->setMaterial(std::make_shared<MurettoPozzoMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

class LegnoPozzoMesh : public Mesh {
  public:
    LegnoPozzoMesh() : Mesh("assets/models/pozzo/legno.obj") {
      
      CarrettoMaterial material;
      this->setMaterial(std::make_shared<CarrettoMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};


class SecchioMesh : public Mesh {
public:
    SecchioMesh() : Mesh("assets/models/pozzo/secchio.obj") {
      
      CarrettoMaterial material;
      this->setMaterial(std::make_shared<CarrettoMaterial>(material));
    }
};

class AcquaPozzoMesh : public Mesh {
public:
    AcquaPozzoMesh() : Mesh("assets/models/pozzo/acqua.obj") {
      WaterMaterial material;
      this->setMaterial(std::make_shared<WaterMaterial>(material));
    }
};

#endif // POZZOMESH_HPP
