#ifndef PBRSHADER_HPP
#define PBRSHADER_HPP

#include <string>
#include "materials/Texture.hpp"
#include "shaders/Shader.hpp"

class PBRShader : public Shader {

public:
    PBRShader()
        : Shader("shaders/PBRVert.spv", "shaders/PBRFrag.spv") {
            int num_textures = 5;

            this->texture_types.resize(num_textures);
            this->texture_types[0] = TextureType::Diffuse;
            this->texture_types[1] = TextureType::Roughness;
            this->texture_types[2] = TextureType::Metallic;
            this->texture_types[3] = TextureType::Normal;
            this->texture_types[4] = TextureType::AmbientOcclusion;
        }

};

#endif // PBRSHADER_HPP