#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include <memory>
#include "objects/Transform.hpp"
#include "lights/Light.hpp"
#include "objects/Mesh.hpp"

class Object
{
public:
  Transform transform;

  Object()
  {
    childrenObjects = std::vector<std::shared_ptr<Object>>();
    meshes = std::vector<std::shared_ptr<Mesh>>();
    transform = Transform();
  }

  ~Object() = default;

  const std::vector<std::shared_ptr<Object>> &getChildrenObjects() const { return childrenObjects; }
  const std::vector<std::shared_ptr<Mesh>> &getMeshes() const { return meshes; }
  const std::vector<std::shared_ptr<Light>> &getLights() const { return lights; }

  void setChildrenObjects(const std::vector<std::shared_ptr<Object>> &childrenObjects) { this->childrenObjects = childrenObjects; }
  void setMeshes(const std::vector<std::shared_ptr<Mesh>> &meshes) { this->meshes = meshes; }
  void setLights(const std::vector<std::shared_ptr<Light>> &lights) { this->lights = lights; }

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

  std::vector<std::pair<std::shared_ptr<Light>, Transform>> getRecursiveLightsTransform() {
    std::vector<std::pair<std::shared_ptr<Light>, Transform>> allLightsTransform;

    // Collect all lights from the current node
    for (const auto& light : lights) {
        auto transformedLight = transform * light->transform;
        allLightsTransform.emplace_back(light, transformedLight);
    }

    // Recursively collect lights from children
    for (const auto& child : childrenObjects) {
        auto childLightsTransform = child->getRecursiveLightsTransform();
        allLightsTransform.insert(allLightsTransform.end(), childLightsTransform.begin(), childLightsTransform.end());
    }

    return allLightsTransform;
  }


private:
  std::vector<std::shared_ptr<Object>> childrenObjects;
  std::vector<std::shared_ptr<Mesh>> meshes;
  std::vector<std::shared_ptr<Light>> lights;
};

#endif // OBJECT_HPP