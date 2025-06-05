#ifndef CARRETTO_HPP
#define CARRETTO_HPP

#include <vector>
#include <memory>
#include <fstream>
#include <random>
#include "scene/natureScene/mesh/Carretto.hpp"
#include "objects/Object.hpp"
#include "utilities/Input.hpp"

class Carretto : public Object
{
public:
  Carretto() : Object()
  { 

std::vector<glm::vec3> positions = {
    { -88.6894f, -5.1454f, 107.5889f },
    { -88.3334f, -6.7566f, 107.5615f },
    { 60.0872f, -6.8003f, 126.8310f },
    { 60.4174f, -8.4033f, 127.0432f },
    { -77.1298f, -5.6590f, 22.6780f },
    { -76.7012f, -7.2500f, 22.5850f },
    { 77.3479f, -1.1143f, 7.6732f },
    { 77.3017f, -2.7594f, 7.7949f }
};

std::vector<glm::vec3> rotations = {
    { 92.2953f, -165.0858f, -9.8433f },
    { 92.2953f, -165.0858f, -9.8433f },
    { -85.0017f, -11.3826f, -169.6094f },
    { -85.0017f, -11.3826f, -169.6094f },
    { 83.6404f, 167.5108f, -11.5951f },
    { 83.6405f, 167.5108f, -11.5951f },
    { 93.3113f, 115.7217f, -0.6648f },
    { 93.3113f, 115.7217f, -0.6648f }
};

std::vector<glm::vec3> scales = {
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f }
};


std::vector<glm::vec3> positionsWheels = {
    { -88.3334f, -6.7566f, 107.5615f },
    { 60.4174f, -8.4033f, 127.0432f },
    { -76.7012f, -7.2500f, 22.5850f },
    { 77.3017f, -2.7594f, 7.7949f }
};

std::vector<glm::vec3> rotationsWheels = {
    { 92.2953f, -165.0858f, -9.8433f },
    { -85.0017f, -11.3826f, -169.6094f },
    { 83.6405f, 167.5108f, -11.5951f },
    { 93.3113f, 115.7217f, -0.6648f }
};

std::vector<glm::vec3> scalesWheels = {
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f },
    { 1.0000f, 1.0000f, 1.0000f }
};



    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.reserve(positions.size());

    for (size_t i = 0; i < positions.size(); ++i)
    {
      auto carretto = std::make_shared<CarrettoMesh>();
      auto carrettowheels = std::make_shared<CarrettoWheels>();

      glm::vec3 pos = positions[i];
      glm::vec3 rot = rotations[i];
      glm::vec3 scale = scales[i];

      carretto->transform.setPosition(pos);
      carretto->transform.setRotation(rot);
      carretto->transform.setScale(scale);

      pos = positionsWheels[i];
      rot = rotationsWheels[i];
      scale = scalesWheels[i];
      carrettowheels->transform.setPosition(pos);
      carrettowheels->transform.setRotation(rot);
      carrettowheels->transform.setScale(scale);

      meshes.push_back(carretto);
      meshes.push_back(carrettowheels);
    }

    this->setMeshes(meshes);
  }
};

#endif // CARRETTO_HPP