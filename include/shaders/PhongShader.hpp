#ifndef PHONGSHADER_HPP
#define PHONGSHADER_HPP

#include <string>
#include "shaders/Shader.hpp"

class PhongShader : public Shader {

public:
    PhongShader()
        : Shader("shaders/PhongVert.spv", "shaders/PhongFrag.spv") {}

};

#endif // PHONGSHADER_HPP