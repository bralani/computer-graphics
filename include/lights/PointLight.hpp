#ifndef POINTLIGHT  
#define POINTLIGHT  

#include "lights/Light.hpp"

class PointLight : public Light {
  public:
    PointLight() = default;
    ~PointLight() = default;
};

#endif // POINTLIGHT  
