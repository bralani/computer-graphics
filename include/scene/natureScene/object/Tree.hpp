#ifndef TREE_HPP
#define TREE_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Tree.hpp"

class Tree : public Object
{
public:
  Tree() : Object()
  {
    auto wood = std::make_shared<TreeWoodMesh>();
    auto leaves = std::make_shared<TreeLeavesMesh>();

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(wood);
    meshes.push_back(leaves);

    this->setMeshes(meshes);
  }

};

#endif // TREE_HPP