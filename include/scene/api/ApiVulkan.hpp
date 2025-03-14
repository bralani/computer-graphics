#ifndef APIVULKAN_HPP
#define APIVULKAN_HPP

#include <glm/glm.hpp>

struct UniformBufferObject {
	alignas(16) glm::mat4 mvpMat;
	alignas(16) glm::mat4 mMat;
	alignas(16) glm::mat4 nMat;
	alignas(16) glm::vec4 overColor;
};

struct GlobalUniformBufferObject {
	alignas(16) glm::vec3 lightDir;
	alignas(16) glm::vec4 lightColor;
	alignas(16) glm::vec3 eyePos;
};

struct Vertex {
	glm::vec3 pos;
	glm::vec2 UV;
	glm::vec3 norm;
};

class ApiVulkan {
public:
    ApiVulkan();
    ~ApiVulkan() = default;
};
  

#endif // APIVULKAN_HPP


