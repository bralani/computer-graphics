#ifndef MULINOOBJECT_HPP
#define MULINOOBJECT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Mulino.hpp"
#include <cmath>

class Mulino : public Object
{
public:
  Mulino() : Object()
  {
    auto ruota = std::make_shared<RuotaMulinoMesh>();
    ruota->transform.setPosition(glm::vec3(-114.795, -9.27008, 32.3105));

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(ruota);

    this->setMeshes(meshes);
  }


  void update() {
    const float rotateSpeed = 20.0f;  // units per second

    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    // Get current transform values
    glm::vec3 rotation = meshes[0]->transform.getRotation();
    rotation.z += (rotateSpeed * deltaTime); // Rotate around Z-axis
    rotation.z = fmod(rotation.z, 360.0f); // Keep rotation within 0-360 degrees
    meshes[0]->transform.setRotation(rotation);

    this->getRecursiveMeshesTransform();
  }

};

#endif // MULINOOBJECT_HPP