#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>

enum TypeLight {
  DIRECTIONAL,
  POINT_LIGHT,
  SPOT
};

class Light {
  public:
    Transform transform;

    Light() = default;
    ~Light() = default;

    glm::vec3 getColor() const { return color; }
    glm::vec3 getDirection() const { return transform.getRotation(); }
    glm::vec3 getPosition() const { return transform.getPosition(); }
    Transform& getGlobalTransform() { return globalTransform; }
    void setGlobalTransform(Transform& transform) { 
      globalTransform = transform;
    }


    float getIntensity() const { return intensity; }
    TypeLight getType() const { return type; }

  protected:
    Transform globalTransform;
    // Light properties
    glm::vec3 color = glm::vec3(1.0f);
    float intensity = 1.0f;
    TypeLight type;
};

#endif // LIGHT_HPP
