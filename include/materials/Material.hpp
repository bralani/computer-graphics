#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <optional>

class Material
{
public:
  Material() = default;
  ~Material() = default;

  void loadTextures();
  void cleanup();

  const std::optional<std::string> &getAlbedoMap() const { return albedoMap; }
  const std::optional<std::string> &getNormalMap() const { return normalMap; }
  const std::optional<std::string> &getMetallicMap() const { return metallicMap; }
  const std::optional<std::string> &getRoughnessMap() const { return roughnessMap; }
  const std::optional<std::string> &getAOMap() const { return aoMap; }

private:
  std::optional<std::string> albedoMap;
  std::optional<std::string> normalMap;
  std::optional<std::string> metallicMap;
  std::optional<std::string> roughnessMap;
  std::optional<std::string> aoMap;
};

#endif // MATERIAL_HPP