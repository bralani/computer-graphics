#ifndef FIENILE_MESH_HPP
#define FIENILE_MESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/FienileMaterial.hpp"

class TettoOpacity : public Mesh {
public:
    TettoOpacity() : Mesh("assets/models/fienile/tetto_opacity.obj") {
      
      TettoFienileMaterial material;
      this->setMaterial(std::make_shared<TettoFienileMaterial>(material));
    }
};

class TettoNoOpacity : public Mesh {
public:
    TettoNoOpacity() : Mesh("assets/models/fienile/tetto_no_opacity.obj") {
      
      TettoFienileMaterial material;
      this->setMaterial(std::make_shared<TettoFienileMaterial>(material));
    }
};

class Tetto3Fienile : public Mesh {
public:
    Tetto3Fienile() : Mesh("assets/models/fienile/tetto_3.obj") {
      
      BoardsFienileMaterial material;
      this->setMaterial(std::make_shared<BoardsFienileMaterial>(material));
    }
};

class EdificioFienile : public Mesh {
public:
    EdificioFienile() : Mesh("assets/models/fienile/edificio.obj") {
      
      PlanksFienileMaterial material;
      this->setMaterial(std::make_shared<PlanksFienileMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};
#endif // FIENILE_MESH_HPP
