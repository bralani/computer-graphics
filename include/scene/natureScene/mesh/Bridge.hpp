#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/BridgeMaterial.hpp"

class BridgeMesh : public Mesh {
public:
    BridgeMesh() : Mesh("assets/models/bridge.obj") {
      
      BridgeMaterial material;
      this->setMaterial(std::make_shared<BridgeMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
      this->setComputeShadows(false);
    }
};

#endif // BRIDGE_HPP
