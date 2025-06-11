#ifndef WALLSOBJECT_HPP
#define WALLSOBJECT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Walls.hpp"

class Walls : public Object
{
public:
  Walls() : Object()
  {
    auto wall = std::make_shared<WallMesh>();
    auto gate = std::make_shared<CancelloMesh>();

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(wall);
    meshes.push_back(gate);

    this->setMeshes(meshes);
  }

  void update(glm::vec3 currentPosition)
  {	
    glm::vec3 position_gate = meshes[1]->transform.getPosition();
    glm::vec3 position_trigger = glm::vec3(-69.5164, 0.335829, -26.8611);

    float distance = glm::distance(currentPosition, position_trigger);
    bool openGate = distance < 15.0f;
    bool update = false;
    if (openGate) {
      if (position_gate.y <= 9.0f) {
        position_gate.y += 0.1f;
        update = true;
      }
    } else {
      if (position_gate.y > 0.0f) {
        position_gate.y -= 0.1f;
        update = true;
      }
    }

    if (update) {
      meshes[1]->transform.setPosition(position_gate);
      this->getRecursiveMeshesTransform();
    }
  }
};

#endif // WALLSOBJECT_HPP