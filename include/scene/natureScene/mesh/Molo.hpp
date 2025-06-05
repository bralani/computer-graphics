#ifndef MOLOMESH_HPP
#define MOLOMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/MoloMaterial.hpp"

class SupportoMoloMesh : public Mesh {
public:
    SupportoMoloMesh() : Mesh("assets/models/molo/supporto.obj") {
      
      SupportoMoloMaterial material;
      this->setMaterial(std::make_shared<SupportoMoloMaterial>(material));
    }
};


class PasserellaMoloMesh : public Mesh {
public:
    PasserellaMoloMesh() : Mesh("assets/models/molo/passerella.obj") {
      
      PasserellaMoloMaterial material;
      this->setMaterial(std::make_shared<PasserellaMoloMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};


class PaliMoloMesh : public Mesh {
public:
    PaliMoloMesh() : Mesh("assets/models/molo/pali.obj") {
      
      PaliMoloMaterial material;
      this->setMaterial(std::make_shared<PaliMoloMaterial>(material));
    }
};

#endif // MOLOMESH_HPP
