#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <memory>
#include "objects/Transform.hpp"
#include "objects/Collision.hpp"
#include "materials/Material.hpp"


class Mesh {
public:
    Transform transform;

    Mesh(const std::string& filename) 
        : filename(filename), transform(), globalTransform(), material(std::make_shared<Material>()) {
    }

    ~Mesh() = default;
        
    const std::shared_ptr<Material>& getMaterial() const { return material; }
    void setMaterial(const std::shared_ptr<Material>& mat) { material = mat; }

    const std::string& getFilename() const { return filename; }
    void setFilename(const std::string& name) { filename = name; }
    
    void setGlobalTransform(Transform& transform) { 
        globalTransform = transform;
    }
    
    void setCollisionTransform() {
        if (!collision) return;
        
        collision->setGlobalTransform(globalTransform);
    }

    Transform& getGlobalTransform() { return globalTransform; }
    const std::shared_ptr<Collision>& getCollision() const { return collision; }

    void setComputeShadows(bool compute) { computeShadows = compute; }
    bool getComputeShadows() const { return computeShadows; }
protected:
    Transform globalTransform;
    std::shared_ptr<Material> material;
    std::string filename;
    std::shared_ptr<Collision> collision = nullptr;
    bool computeShadows = true;
};

#endif // MESH_HPP
