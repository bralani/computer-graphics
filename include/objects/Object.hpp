#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include <memory>
#include "objects/Transform.hpp"
#include "objects/Mesh.hpp"

class Object
{
public:
  Transform transform;

  Object(std::vector<std::shared_ptr<Object>> childrenObjects,
         std::vector<std::shared_ptr<Mesh>> meshes) : childrenObjects(childrenObjects), meshes(meshes)
  {
    transform = Transform();
  }

  Object(std::vector<std::shared_ptr<Mesh>> meshes) : meshes(meshes)
  {
    childrenObjects = std::vector<std::shared_ptr<Object>>();
    transform = Transform();
  }

  Object(std::vector<std::shared_ptr<Object>> childrenObjects) : childrenObjects(childrenObjects)
  {
    meshes = std::vector<std::shared_ptr<Mesh>>();
    transform = Transform();
  }

  Object()
  {
    childrenObjects = std::vector<std::shared_ptr<Object>>();
    meshes = std::vector<std::shared_ptr<Mesh>>();
    transform = Transform();
  }

  ~Object() = default;

  const std::vector<std::shared_ptr<Object>> &getChildrenObjects() const { return childrenObjects; }
  const std::vector<std::shared_ptr<Mesh>> &getMeshes() const { return meshes; }

  const std::vector<std::shared_ptr<Mesh>> getRecursiveMeshes()
  {
    std::vector<std::shared_ptr<Mesh>> allMeshes = meshes;

    for (auto &child : childrenObjects)
    {
      auto childMeshes = child->getRecursiveMeshes();
      allMeshes.insert(allMeshes.end(), childMeshes.begin(), childMeshes.end());
    }

    return allMeshes;
  }

private:
  std::vector<std::shared_ptr<Object>> childrenObjects;
  std::vector<std::shared_ptr<Mesh>> meshes;
};

#endif // OBJECT_HPP