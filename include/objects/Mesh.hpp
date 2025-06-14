#ifndef MESH_HPP
#define MESH_HPP

class Object; 

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

    virtual ~Mesh() = default;
        
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

    Object* getPickRoot() const { return pickRoot; }
    void    setPickRoot(Object* o) { pickRoot = o; }

    virtual const char* getDebugName() const { return "Mesh"; }   // 
protected:
    Transform globalTransform;
    std::shared_ptr<Material> material;
    std::string filename;
    std::shared_ptr<Collision> collision = nullptr;
    bool computeShadows = true;
    Object* pickRoot = nullptr;
};

#endif // MESH_HPP
