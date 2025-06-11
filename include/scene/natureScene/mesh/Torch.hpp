#ifndef torch_mesh_hpp
#define torch_mesh_hpp

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/TorchMaterial.hpp"

class TorchMetalloMesh : public Mesh {
public:
    TorchMetalloMesh() : Mesh("assets/models/torch/metallo.obj") {
      
      TorchMaterial material;
      this->setMaterial(std::make_shared<TorchMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};


class TorchMesh : public Mesh {
public:
    TorchMesh() : Mesh("assets/models/torch/torch.obj") {
      
      TorchMaterial material;
      this->setMaterial(std::make_shared<TorchMaterial>(material));
      this->collision = std::make_shared<Collision>(filename, globalTransform);
      this->collision->setActive(true);
    }
};

#endif // torch_mesh_hpp
