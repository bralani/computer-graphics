#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

class Shader {
protected:
    std::vector<TextureType> texture_types;
    std::string vertexPath;
    std::string fragmentPath;

public:
    Shader() = default;
    ~Shader() = default;

    Shader(const std::string& vertexPath, const std::string& fragmentPath)
        : vertexPath(vertexPath), fragmentPath(fragmentPath) {}

    std::string getVertexPath() const { return vertexPath; }
    std::string getFragmentPath() const { return fragmentPath; }

    void setVertexPath(const std::string& path) { vertexPath = path; }
    void setFragmentPath(const std::string& path) { fragmentPath = path; }

    std::vector<TextureType> getTextureTypes() { return texture_types; }
};

#endif // SHADER_HPP