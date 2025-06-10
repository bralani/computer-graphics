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
            {-92.6671f, -6.7006f, 112.6654f},
            {-89.5084f, -6.6715f, 113.2875f},
            {-86.3846f, -6.7552f, 114.2531f},
            {-95.7856f, -6.6315f, 112.0942f},
            {-98.8385f, -6.6784f, 112.2332f}};

        std::vector<glm::vec3> rotations = {
            {98.1382f, 0.0000f, -90.0000f},
            {-79.4368f, 0.0000f, -90.0000f},
            {-73.9643f, 0.0000f, -90.0000f},
            {98.1382f, 0.0000f, -90.0000f},
            {64.7623f, -0.0000f, -91.3775f}};

        std::vector<glm::vec3> scales = {
            {1.0000f, 1.0000f, 1.0000f},
            {1.0000f, 1.0000f, 1.0000f},
            {1.0000f, 1.0000f, 1.0000f},
            {1.0000f, 1.0000f, 1.0000f},
            {1.0000f, 1.0000f, 1.0000f}};

        auto meshes = std::vector<std::shared_ptr<Mesh>>();
        meshes.reserve(positions.size());

        for (size_t i = 0; i < positions.size(); ++i)
        {
            auto fence = std::make_shared<FenceMesh>();
            glm::vec3 pos = positions[i];
            glm::vec3 rot = rotations[i];
            glm::vec3 scale = scales[i];

            fence->transform.setPosition(pos);
            fence->transform.setRotation(rot);
            fence->transform.setScale(scale);

            meshes.push_back(fence);
        }

        this->setMeshes(meshes);
    }
};

#endif // FENCES_HPP