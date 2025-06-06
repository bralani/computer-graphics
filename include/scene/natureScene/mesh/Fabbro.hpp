#ifndef FABBRO_MESH_HPP
#define FABBRO_MESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/FabbroMaterial.hpp"

class LegnoFabbro : public Mesh {
public:
    LegnoFabbro() : Mesh("assets/models/fabbro/legno.obj") {
      LegnoFabbroMaterial material;
      this->setMaterial(std::make_shared<LegnoFabbroMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

class ScudiFabbro : public Mesh {
public:
    ScudiFabbro() : Mesh("assets/models/fabbro/scudi.obj") {
      ScudiFabbroMaterial material;
      this->setMaterial(std::make_shared<ScudiFabbroMaterial>(material));
    }
};

class SpadeFabbro : public Mesh {
public:
    SpadeFabbro() : Mesh("assets/models/fabbro/spade.obj") {
      SpadeFabbroMaterial material;
      this->setMaterial(std::make_shared<SpadeFabbroMaterial>(material));
    }
};

#endif // FABBRO_MESH_HPP
