#ifndef MULINOMESH_HPP
#define MULINOMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/MulinoMaterial.hpp"

class RuotaMulinoMesh : public Mesh {
public:
    RuotaMulinoMesh() : Mesh("assets/models/mulino/ruota.obj") {
      
      RuotaMulinoMaterial material;
      this->setMaterial(std::make_shared<RuotaMulinoMaterial>(material));
    }
};

#endif // MULINOMESH_HPP
