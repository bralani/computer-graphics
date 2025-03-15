#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <optional>

class Material
{
public:
  Material(
      const std::optional<std::string> &albedoPath = std::nullopt,
      const std::optional<std::string> &normalPath = std::nullopt,
      const std::optional<std::string> &metallicPath = std::nullopt,
      const std::optional<std::string> &roughnessPath = std::nullopt,
      const std::optional<std::string> &aoPath = std::nullopt);
  ~Material();

  void loadTextures();
  void cleanup();

  const std::optional<std::string> &getAlbedoMap() const { return albedoMap; }
  const std::optional<std::string> &getNormalMap() const { return normalMap; }
  const std::optional<std::string> &getMetallicMap() const { return metallicMap; }
  const std::optional<std::string> &getRoughnessMap() const { return roughnessMap; }
  const std::optional<std::string> &getAOMap() const { return aoMap; }

private:
  void loadTextureFromFile(const std::string &path);

  std::optional<std::string> albedoMap;
  std::optional<std::string> normalMap;
  std::optional<std::string> metallicMap;
  std::optional<std::string> roughnessMap;
  std::optional<std::string> aoMap;
};

#endif // MATERIAL_HPP