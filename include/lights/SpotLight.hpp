#ifndef SPOTLIGHT_HPP  
#define SPOTLIGHT_HPP  

#include "lights/Light.hpp"

class SpotLight : public Light {
  public:
    SpotLight() = default;
    ~SpotLight() = default;
};

#endif // SPOTLIGHT_HPP  
