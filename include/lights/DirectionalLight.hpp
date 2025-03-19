#ifndef DIRECTIONALLIGHT_HPP  
#define DIRECTIONALLIGHT_HPP  

#include "lights/Light.hpp"

class DirectionalLight : public Light {
  public:
    DirectionalLight() : Light() {}

    DirectionalLight(glm::vec3 color, glm::vec3 direction, float intensity = 1.0f) : Light() {
        this->type = TypeLight::DIRECTIONAL;
        this->color = color;
        this->transform.setRotation(direction);
        this->intensity = intensity;
    }
    ~DirectionalLight() = default;
};

#endif // DIRECTIONALLIGHT_HPP  
