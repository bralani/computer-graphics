#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <memory>
#include "objects/Transform.hpp"
#include "materials/Material.hpp"


class Mesh {
public:
    Transform transform;

    Mesh(const std::string& filename) 
        : filename(filename), transform(), material(std::make_shared<Material>()) {
    }

    ~Mesh() = default;
        
    const std::shared_ptr<Material>& getMaterial() const { return material; }
    void setMaterial(const std::shared_ptr<Material>& mat) { material = mat; }

    const std::string& getFilename() const { return filename; }
    void setFilename(const std::string& name) { filename = name; }
    
private:
    std::shared_ptr<Material> material;
    std::string filename;
};

#endif // MESH_HPP
