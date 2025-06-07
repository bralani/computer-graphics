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
            {-73.8280f, -6.9533f, 13.1550f},
            {81.7730f, -3.8250f, 5.6644f},
            {79.6695f, -3.4845f, 9.7679f},
            {-29.2574f, -2.2422f, -0.0082f},
            {-93.2699f, -7.3207f, 109.8316f},
            {-116.0407f, -9.3167f, 93.8215f},
            {103.1742f, -7.7211f, 153.4709f}};

        std::vector<glm::vec3> rotations = {
            {-1.2770f, 167.2037f, -5.6324f},
            {-1.2770f, 122.5920f, -5.6324f},
            {-1.2770f, -90.7522f, -5.6324f},
            {-1.2770f, 36.0092f, -5.6324f},
            {2.7902f, -128.9688f, -5.1953f},
            {7.8971f, -128.3259f, -9.2501f},
            {4.7264f, -128.0032f, -8.0223f}};

        auto meshes = std::vector<std::shared_ptr<Mesh>>();
        meshes.reserve(positions.size());

        for (size_t i = 0; i < positions.size(); ++i)
        {
            auto carretto = std::make_shared<CarrettoMesh>();

            glm::vec3 pos = positions[i];
            glm::vec3 rot = rotations[i];

            carretto->transform.setPosition(pos);
            carretto->transform.setRotation(rot);
            
            meshes.push_back(carretto);
        }

        this->setMeshes(meshes);
    }
};

#endif // CARRETTO_HPP