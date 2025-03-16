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

  std::vector<std::pair<std::shared_ptr<Mesh>, Transform>> getRecursiveMeshesTransform() {
    std::vector<std::pair<std::shared_ptr<Mesh>, Transform>> allMeshesTransform;

    // Collect all meshes from the current node
    for (const auto& mesh : meshes) {
        auto transformedMesh = transform * mesh->transform;
        allMeshesTransform.emplace_back(mesh, transformedMesh);
    }

    // Recursively collect meshes from children
    for (const auto& child : childrenObjects) {
        auto childMeshesTransform = child->getRecursiveMeshesTransform();
        allMeshesTransform.insert(allMeshesTransform.end(), childMeshesTransform.begin(), childMeshesTransform.end());
    }

    return allMeshesTransform;
}


private:
  std::vector<std::shared_ptr<Object>> childrenObjects;
  std::vector<std::shared_ptr<Mesh>> meshes;
};

#endif // OBJECT_HPP