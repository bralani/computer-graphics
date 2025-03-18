#ifndef PHONGSHADER_HPP
#define PHONGSHADER_HPP

#include <string>
#include "shaders/Shader.hpp"

class PhongShader : public Shader {

public:
    PhongShader()
        : Shader("shaders/PhongVert.spv", "shaders/PhongFrag.spv") {
            int num_textures = 1;

            this->texture_types.resize(num_textures);
            this->texture_types[0] = TextureType::Diffuse;
        }

};

#endif // PHONGSHADER_HPP