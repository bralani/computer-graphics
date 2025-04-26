#ifndef TREEMESH_HPP
#define TREEMESH_HPP

#include <string>
#include "objects/Mesh.hpp"
#include "scene/natureScene/materials/TreeMaterial.hpp"

class TreeWoodMesh : public Mesh {
public:
  TreeWoodMesh() : Mesh("assets/models/tree.obj") {
    TreeWoodMaterial material;
    this->setMaterial(std::make_shared<TreeWoodMaterial>(material));
  }
};

class TreeLeavesMesh : public Mesh {
public:
  TreeLeavesMesh() : Mesh("assets/models/leaves.obj") {
    
    TreeLeavesMaterial material;
    this->setMaterial(std::make_shared<TreeLeavesMaterial>(material));
  }
};

#endif // TREEMESH_HPP
