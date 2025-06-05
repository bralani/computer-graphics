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
    { -113.2393f, -9.3111f, 5.1487f },
    { -115.5943f, -10.8878f, 8.1783f },
    { -109.3573f, -11.0030f, 9.3582f },
    { -105.2738f, -10.9058f, 11.2190f },
    { -105.2738f, -8.9624f, 11.2190f },
    { -109.1198f, -7.4568f, 10.0461f },
    { -100.9703f, -11.2319f, 6.0174f },
    { -103.0783f, -11.0317f, 1.1461f },
    { -103.1121f, -9.2187f, 2.4210f },
    { -104.4314f, -11.3759f, 4.0449f },
    { -107.1997f, -12.4475f, 0.3976f },
    { -78.4905f, -6.8930f, 24.3593f },
    { -78.3514f, -4.8465f, 25.0763f },
    { 124.9881f, -6.8375f, -6.8394f }
};

std::vector<glm::vec3> rotations = {
    { 91.8180f, -56.8301f, -52.3397f },
    { 90.0000f, 28.3314f, 0.0000f },
    { 90.0000f, -11.8527f, 0.0000f },
    { 90.0000f, -48.9793f, 0.0000f },
    { 90.0000f, -48.9793f, 0.0000f },
    { 13.7098f, -114.0544f, -50.4511f },
    { 90.0000f, -48.9793f, 0.0000f },
    { 97.4995f, -45.5553f, -7.6756f },
    { 97.4995f, -84.7420f, -7.6756f },
    { 97.4995f, -72.5938f, -7.6756f },
    { 97.4995f, -119.5507f, -7.6756f },
    { 99.2214f, -13.1549f, 9.0771f },
    { 99.2214f, -13.1549f, 9.0771f },
    { 108.4987f, -103.6926f, 6.9438f }
};

std::vector<glm::vec3> scales = {
    { 5.4246f, 5.4246f, 5.4246f },
    { 4.9006f, 4.9006f, 4.9006f },
    { 4.9006f, 4.9006f, 4.9006f },
    { 4.9006f, 4.9006f, 4.9006f },
    { 4.9006f, 4.9006f, 4.9006f },
    { 4.9006f, 4.9006f, 4.9006f },
    { 4.9006f, 4.9006f, 4.9006f },
    { 4.9006f, 4.9006f, 4.9006f },
    { 4.9006f, 4.9006f, 4.9006f },
    { 4.9006f, 4.9006f, 4.9006f },
    { 4.9006f, 4.9006f, 4.9006f },
    { 4.9006f, 4.9006f, 4.9006f },
    { 4.9006f, 4.9006f, 4.9006f },
    { 4.9006f, 4.9006f, 4.9006f }
};



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