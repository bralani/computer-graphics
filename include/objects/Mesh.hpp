#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <glm/glm.hpp>
#include <string>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

struct Material {
    glm::vec3 color;
    float shininess;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const Material& material);
    Mesh(const std::string& filename); // Costruttore per leggere da file
    ~Mesh();
    
    void createBuffers();
    void cleanup();
    
    const std::vector<Vertex>& getVertices() const { return vertices; }
    const std::vector<uint32_t>& getIndices() const { return indices; }
    uint32_t getIndexCount() const { return static_cast<uint32_t>(indices.size()); }
    
    const glm::vec3& getPosition() const { return position; }
    const glm::vec3& getRotation() const { return rotation; }
    const glm::vec3& getScale() const { return scale; }
    const Material& getMaterial() const { return material; }
    
    void setPosition(const glm::vec3& pos) { position = pos; }
    void setRotation(const glm::vec3& rot) { rotation = rot; }
    void setScale(const glm::vec3& scl) { scale = scl; }
    void setMaterial(const Material& mat) { material = mat; }
    
private:
    void loadFromFile(const std::string& filename); // Metodo per leggere da file
    void createVertexBuffer();
    void createIndexBuffer();
    
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    Material material;
    
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
};

#endif // MESH_HPP
