#ifndef DIRECTIONALLIGHT_HPP  
#define DIRECTIONALLIGHT_HPP  

#include "lights/Light.hpp"

class DirectionalLight : public Light {
  public:
    DirectionalLight() = default;
    ~DirectionalLight() = default;
};

#endif // DIRECTIONALLIGHT_HPP  
