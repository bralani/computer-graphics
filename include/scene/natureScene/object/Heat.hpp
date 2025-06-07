#ifndef HEAT_HPP
#define HEAT_HPP

#include <vector>
#include <memory>
#include <fstream>
#include <random>
#include "scene/natureScene/mesh/Heat.hpp"
#include "objects/Object.hpp"
#include "utilities/Input.hpp"

class Heat : public Object
{
public:
  Heat() : Object()
  {

    std::vector<glm::vec3> positions = {
        {-113.2393f, -9.3111f, 5.1487f},
        {-115.5943f, -11.1784f, 8.1783f},
        {-109.3573f, -11.0030f, 9.3582f},
        {-119.0883f, -11.5087f, 17.9605f},
        {-119.0883f, -9.5653f, 17.9605f},
        {-109.1198f, -7.4568f, 10.0461f},
        {-74.3579f, -7.3628f, 13.6776f},
        {-74.3129f, -6.6997f, 13.9099f},
        {124.9881f, -6.8375f, -6.8394f}};

    std::vector<glm::vec3> rotations = {
        {91.8180f, -56.8301f, -52.3397f},
        {90.0000f, 28.3314f, 0.0000f},
        {90.0000f, -11.8527f, 0.0000f},
        {90.0000f, -71.4066f, 0.0000f},
        {90.0000f, -71.4066f, 0.0000f},
        {13.7098f, -114.0544f, -50.4511f},
        {99.2214f, -13.1549f, 9.0771f},
        {99.2214f, -13.1549f, 9.0771f},
        {108.4987f, -103.6926f, 6.9438f}};

    std::vector<glm::vec3> scales = {
        {5.4246f, 5.4246f, 5.4246f},
        {4.9006f, 4.9006f, 4.9006f},
        {4.9006f, 4.9006f, 4.9006f},
        {4.9006f, 4.9006f, 4.9006f},
        {4.9006f, 4.9006f, 4.9006f},
        {4.9006f, 4.9006f, 4.9006f},
        {1.5878f, 1.5878f, 1.5878f},
        {1.5878f, 1.5878f, 1.5878f},
        {4.9006f, 4.9006f, 4.9006f}};

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.reserve(positions.size());

    for (size_t i = 0; i < positions.size(); ++i)
    {
      auto heat = std::make_shared<HeatMesh>();
      glm::vec3 pos = positions[i];
      glm::vec3 rot = rotations[i];
      glm::vec3 scale = scales[i];

      heat->transform.setPosition(pos);
      heat->transform.setRotation(rot);
      heat->transform.setScale(scale);

      meshes.push_back(heat);
    }

    this->setMeshes(meshes);
  }
};

#endif // HEAT_HPP