#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include "objects/Transform.hpp"
#include "objects/Mesh.hpp"

class Object {
public:
    Transform transform;

    Object(std::vector<std::shared_ptr<Mesh>> meshes) : meshes(meshes) {
      transform = Transform();
    }
    ~Object() = default;

    const std::vector<std::shared_ptr<Mesh>>& getMeshes() const { return meshes; }
private:
    std::vector<std::shared_ptr<Mesh>> meshes;
};

#endif // OBJECT_HPP