#ifndef APIVULKAN_HPP
#define APIVULKAN_HPP

class Scene;  // Forward declaration

#include <glm/glm.hpp>


class ApiVulkan {
public:
    ApiVulkan(Scene *scene);
    ~ApiVulkan() = default;
private:
    Scene *scene;
};
  

#endif // APIVULKAN_HPP


