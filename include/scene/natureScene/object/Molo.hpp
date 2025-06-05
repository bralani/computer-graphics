#ifndef MOLOOBJECT_HPP
#define MOLOOBJECT_HPP

#include <vector>
#include <memory>
#include "scene/natureScene/mesh/Molo.hpp"

class Molo : public Object
{
public:
  Molo() : Object()
  {
    auto supporto = std::make_shared<SupportoMoloMesh>();
    
    auto passerella = std::make_shared<PasserellaMoloMesh>();

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.push_back(supporto);
    meshes.push_back(passerella);

    std::vector<glm::vec3> pali_positions = {
        { 148.5736f, -13.8476f, 82.7291f },
        { 152.4440f, -13.8476f, 83.2285f },
        { 156.7305f, -13.8476f, 83.6447f },
        { 161.4332f, -13.8476f, 84.2689f },
        { 166.1775f, -13.8476f, 84.8099f },
        { 170.3392f, -13.8476f, 85.3093f },
        { 149.4726f, -13.8476f, 76.8561f },
        { 153.3429f, -13.8476f, 77.2723f },
        { 157.6711f, -13.8476f, 77.6885f },
        { 162.2905f, -13.8476f, 78.1463f },
        { 166.7435f, -13.8476f, 78.7705f },
        { 171.1133f, -13.8476f, 79.1034f }
    };
    
    for (size_t i = 0; i < pali_positions.size(); ++i)
    {
        auto pali = std::make_shared<PaliMoloMesh>();
        glm::vec3 pos = pali_positions[i];
        pali->transform.setPosition(pos);
        meshes.push_back(pali);
    }

    this->setMeshes(meshes);
  }

};

#endif // MOLOOBJECT_HPP