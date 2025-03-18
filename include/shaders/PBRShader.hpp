#ifndef PBRSHADER_HPP
#define PBRSHADER_HPP

#include <string>
#include "materials/Texture.hpp"
#include "shaders/Shader.hpp"

class PBRShader : public Shader {

public:
    PBRShader()
        : Shader("shaders/PBRVert.spv", "shaders/PBRFrag.spv") {
            int num_textures = 3;

            this->texture_types.resize(num_textures);
            this->texture_types[0] = TextureType::Diffuse;
            this->texture_types[1] = TextureType::Roughness;
            this->texture_types[2] = TextureType::Metallic;
        }

};

#endif // PBRSHADER_HPP