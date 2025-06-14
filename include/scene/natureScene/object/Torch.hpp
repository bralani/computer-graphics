#ifndef TORCH_HPP
#define TORCH_HPP

#include <vector>
#include <memory>
#include <fstream>
#include <random>
#include "lights/PointLight.hpp"
#include "scene/natureScene/mesh/Torch.hpp"
#include "objects/Object.hpp"
#include "utilities/Input.hpp"

class Torch : public Object
{
public:
    Torch() : Object()
    {
        auto meshes = std::vector<std::shared_ptr<Mesh>>();
        meshes.reserve(2);

        auto metallo = std::make_shared<TorchMetalloMesh>();
        meshes.push_back(metallo);

        auto torch = std::make_shared<TorchMesh>();
        meshes.push_back(torch);

        this->setMeshes(meshes);

        PointLight pointLight(
            glm::vec3(1.0, 0.45, 0.1),
            glm::vec3(0.0f, 1.5f, 0.0f),
            0.0f);

        this->setLights({std::make_shared<PointLight>(pointLight)});
    }

    const char *getDebugName() const override { return "Torch"; }
};

class Torchs : public Object
{
public:
    Torchs() : Object()
    {

        std::vector<glm::vec3> positions = {
            {-10.9688f, -0.5361f, 15.8891f},
            {89.5666f, -1.2068f, 14.1494f},
            {26.8758f, -5.4684f, 148.4068f}};

        std::vector<glm::vec3> rotations = {
            {0.0000f, -16.7304f, 0.0000f},
            {0.0000f, -16.7304f, 0.0000f},
            {0.0000f, 163.0008f, 0.0000f}};

        std::vector<glm::vec3> scales = {
            {1.0000f, 1.0000f, 1.0000f},
            {1.0000f, 1.0000f, 1.0000f},
            {1.0000f, 1.0000f, 1.0000f}};

        auto torchchildren = std::vector<std::shared_ptr<Object>>();

        for (size_t i = 0; i < positions.size(); ++i)
        {
            auto torch = std::make_shared<Torch>();

            glm::vec3 pos = positions[i];
            glm::vec3 rot = rotations[i];
            glm::vec3 scale = scales[i];

            torch->transform.setPosition(pos);
            torch->transform.setRotation(rot);
            torch->transform.setScale(scale);

            torchchildren.push_back(torch);
        }

        this->setChildrenObjects(torchchildren);
    }
};

#endif // TORCH_HPP