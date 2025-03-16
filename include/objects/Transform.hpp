#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vector>
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


class Transform
{
public:
  Transform(const glm::vec3 &pos = glm::vec3(0.0f),
            const glm::vec3 &rot = glm::vec3(0.0f),
            const glm::vec3 &scl = glm::vec3(1.0f))
      : position(pos), rotation(rot), scale(scl) {}
  ~Transform() = default;

  const glm::vec3 &getPosition() const { return position; }
  const glm::vec3 &getRotation() const { return rotation; }
  const glm::vec3 &getScale() const { return scale; }
  glm::mat4 getTransform() { return updateTransform(); }

  void setPosition(const glm::vec3 &pos) { 
    position = pos;
    dirty = true;
  }
  void setRotation(const glm::vec3 &rot) { 
    rotation = rot; 
    dirty = true;
  }
  void setScale(const glm::vec3 &scl) { 
    scale = scl; 
    dirty = true;
  }

  Transform operator*(Transform &other)
  {
    Transform newTransform;

    // Compute the global transform matrices
    glm::mat4 thisMatrix = getTransform();
    glm::mat4 otherMatrix = other.getTransform();

    // Multiply the matrices to get the new global transform
    glm::mat4 combinedMatrix = thisMatrix * otherMatrix;

    // Decompose the resulting matrix into position, rotation, and scale
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::quat rotationQuat;
    glm::decompose(combinedMatrix, newTransform.scale, rotationQuat, newTransform.position, skew, perspective);
    
    newTransform.rotation = glm::degrees(glm::eulerAngles(rotationQuat));

    return newTransform;
  }

private:
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  bool dirty = true;
  glm::mat4 transform;

  glm::mat4 updateTransform()
  {
    if(!dirty) return transform;

    transform = glm::mat4(1.0f);

    // Translation
    transform = glm::translate(transform, position);

    // Rotation
    transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0)); // X-axis
    transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0)); // Y-axis
    transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1)); // Z-axis

    // Scaling
    transform = glm::scale(transform, scale);

    dirty = false;

    return transform;
  }
};

#endif // TRANSFORM_HPP