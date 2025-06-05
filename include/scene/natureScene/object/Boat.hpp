#ifndef BOAT_HPP
#define BOAT_HPP

#include <vector>
#include <memory>
#include "objects/Object.hpp"
#include "scene/natureScene/mesh/Boat.hpp"
#include "utilities/Input.hpp"

class Boat : public Object
{
public:
  Boat() : Object()
  {
    auto boatMesh = std::make_shared<BoatMesh>();
    this->boatMesh = boatMesh;

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(boatMesh);

    this->transform.setPosition(glm::vec3(155.022, -13.55, 87.8323));
    this->transform.setRotation(glm::vec3(0, -77.4445, 0));

    this->setMeshes(meshes);
  }

  std::shared_ptr<BoatMesh> getBoatMesh() const { return boatMesh; }

  void update() {
    if (!isActive)
      return;

    // Movement parameters
    const float moveSpeed = 20.0f;  // units per second
    const float turnSpeed = 90.0f; // degrees per second

    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    // Get current transform values
    glm::vec3 position = transform.getPosition();
    glm::vec3 rotation = transform.getRotation(); // Assuming rotation is stored in degrees

    // Handle keyboard input
    // Rotation (A/D)
    if (Input::getKey(GLFW_KEY_A)) {
      rotation.y += turnSpeed * deltaTime;
    }
    if (Input::getKey(GLFW_KEY_D)) {
      rotation.y -= turnSpeed * deltaTime;
    }

    // Convert rotation to radians for calculations
    float yawRad = glm::radians(rotation.y);

    // Calculate forward direction vector
    glm::vec3 moveDirection(
        sin(yawRad),
        0.0f,
        cos(yawRad)
    );

    // Movement (W/S)
	  if (Input::getKey(GLFW_KEY_W)) {
      position += moveDirection * moveSpeed * deltaTime;
    }
    if (Input::getKey(GLFW_KEY_S)) {
      position -= moveDirection * moveSpeed * deltaTime;
    }

    // Update transform
    transform.setPosition(position);
    transform.setRotation(rotation);

    // Update the global transform of the boat mesh
    this->getRecursiveMeshesTransform();
  }

private:
  std::shared_ptr<BoatMesh> boatMesh;
  bool isActive = true;
};

#endif // BOAT_HPP