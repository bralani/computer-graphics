#ifndef POINTLIGHT_HPP  
#define POINTLIGHT_HPP  

#include "lights/Light.hpp"

class PointLight : public Light {
  public:
    PointLight() : Light() {}

    PointLight(glm::vec3 color, glm::vec3 position, float intensity = 1.0f) : Light() {
        this->type = TypeLight::POINT;
        this->color = color;
        this->transform.setPosition(position);
        this->intensity = intensity;
    }
    ~PointLight() = default;
};

#endif // POINTLIGHT_HPP  
