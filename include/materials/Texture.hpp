#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <vector>
#include <iostream>

// Enum per i tipi di texture
enum class TextureType {
    Diffuse,
    Normal,
    Roughness,
    Metallic,
    Specular,
    AmbientOcclusion,
    Emissive,
    Height,
    HDRI
};


class Texture {
private:
    std::string path;
    TextureType type;

public:
    Texture() = default;
    Texture(const std::string& path, TextureType type) : path(path), type(type) {}

    std::string getPath() const { return path; }
    TextureType getType() const { return type; }
};

#endif // TEXTURE_HPP