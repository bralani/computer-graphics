#ifndef FENCES_HPP
#define FENCES_HPP

#include <vector>
#include <memory>
#include <fstream>
#include <random>
#include "scene/natureScene/mesh/Fence.hpp"
#include "objects/Object.hpp"
#include "utilities/Input.hpp"

class Fences : public Object
{
public:
  Fences() : Object()
  { 
std::vector<glm::vec3> positions = {
    { 117.0866f, -9.9268f, 35.8794f },
};

std::vector<glm::vec3> rotations = {
    { 52.0980f, -23.6748f, -93.3952f },
};

std::vector<glm::vec3> scales = {
    { 1.0000f, 1.0000f, 1.0000f }
};


    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.reserve(positions.size());

    for (size_t i = 0; i < positions.size(); ++i)
    {
      auto fence = std::make_shared<FenceMesh>();
      glm::vec3 pos = positions[i];
      glm::vec3 rot_quat = rotations[i];
      glm::vec3 scale = scales[i];

      fence->transform.setPosition(pos);
      //fence->transform.setRotation(rot_quat);
      fence->transform.setScale(scale);

      meshes.push_back(fence);
    }

    this->setMeshes(meshes);
  }
  
  void update() {

    // Movement parameters
    const float turnSpeed = 0.5f;

    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;
    // Prendi il quaternione di rotazione attuale
    glm::quat currentRotation = meshes[0]->transform.getRotationQuat();

    float angleIncrement = turnSpeed * deltaTime; // Angolo di rotazione per questo frame

    if (Input::getKey(GLFW_KEY_F)) {
        glm::quat deltaRotation = glm::angleAxis(angleIncrement, glm::vec3(1.0f, 0.0f, 0.0f)); // Asse X del mondo
        currentRotation = deltaRotation * currentRotation;
    }
    if (Input::getKey(GLFW_KEY_G)) {
        glm::quat deltaRotation = glm::angleAxis(-angleIncrement, glm::vec3(1.0f, 0.0f, 0.0f));
        currentRotation = deltaRotation * currentRotation;
    }

    if (Input::getKey(GLFW_KEY_H)) {
        glm::quat deltaRotation = glm::angleAxis(angleIncrement, glm::vec3(0.0f, 1.0f, 0.0f)); // Asse Y del mondo
        currentRotation = deltaRotation * currentRotation;
    }
    if (Input::getKey(GLFW_KEY_J)) {
        glm::quat deltaRotation = glm::angleAxis(-angleIncrement, glm::vec3(0.0f, 1.0f, 0.0f));
        currentRotation = deltaRotation * currentRotation;
    }

    if (Input::getKey(GLFW_KEY_K)) {
        glm::quat deltaRotation = glm::angleAxis(angleIncrement, glm::vec3(0.0f, 0.0f, 1.0f)); // Asse Z del mondo
        currentRotation = deltaRotation * currentRotation;
    }
    if (Input::getKey(GLFW_KEY_L)) {
        glm::quat deltaRotation = glm::angleAxis(-angleIncrement, glm::vec3(0.0f, 0.0f, 1.0f));
        currentRotation = deltaRotation * currentRotation;
    }

    currentRotation = glm::normalize(currentRotation);

    // Stampa per debug (includi w!)
    std::cout << "Rotation Quat: w=" << currentRotation.w
              << ", x=" << currentRotation.x
              << ", y=" << currentRotation.y
              << ", z=" << currentRotation.z << std::endl;

    // Aggiorna la trasformazione
    meshes[0]->transform.setRotationQuat(currentRotation);


    // Update the global transform of the boat mesh
    this->getRecursiveMeshesTransform();
  }
};

#endif // FENCES_HPP