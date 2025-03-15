#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include "objects/Transform.hpp"
#include "materials/Material.hpp"


class Mesh {
public:
    Transform transform;

    Mesh(const std::string& filename) : filename(filename) {
        material = Material();
        transform = Transform();
    }

    ~Mesh() = default;
        
    const Material& getMaterial() const { return material; }
    void setMaterial(const Material& mat) { material = mat; }

    const std::string& getFilename() const { return filename; }
    void setFilename(const std::string& name) { filename = name; }
private:
    Material material;
    std::string filename;
};

#endif // MESH_HPP
