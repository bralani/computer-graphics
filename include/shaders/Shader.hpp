#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

class Shader {
private:
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
};

#endif // SHADER_HPP