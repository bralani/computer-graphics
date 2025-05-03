#include "objects/Collision.hpp"
#include <algorithm>

Collision::~Collision() {
    delete rigidBody;
    delete motionState;
    delete collisionShape;
    delete triangleMesh;
}

Collision::Collision(const std::string& filename, const Transform& globalTransform) {
    this->globalTransform = std::make_shared<Transform>(globalTransform);
    loadObjMesh(filename);
    

    createRigidBody();
}
void Collision::loadObjMesh(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") { 
            // Vertex position (unchanged)
            float x, y, z;
            iss >> x >> y >> z;
            vertices.emplace_back(x, y, z);
        }
        else if (prefix == "f") { 
            // New face parsing logic
            std::vector<unsigned int> faceIndices;
            std::string vertexInfo;
            
            while (iss >> vertexInfo) {
                // Replace slashes with spaces to split components
                std::replace(vertexInfo.begin(), vertexInfo.end(), '/', ' ');
                std::istringstream viss(vertexInfo);
                
                unsigned int vIndex, vtIndex, vnIndex;
                viss >> vIndex;  // We only need the vertex index for collision
                
                // Handle negative indices (relative addressing)
                if (vIndex < 0) vIndex = vertices.size() + vIndex + 1;
                else vIndex--;  // OBJ indices are 1-based
                
                faceIndices.push_back(vIndex);
            }
            
            // Triangulate face (supports polygons with >3 vertices)
            for (size_t i = 2; i < faceIndices.size(); i++) {
                indices.insert(indices.end(), {
                    faceIndices[0], 
                    faceIndices[i-1], 
                    faceIndices[i]
                });
            }
        }
    }
    file.close();

    // Create Bullet triangle mesh with safety checks
    triangleMesh = new btTriangleMesh();
    for (size_t i = 0; i < indices.size(); i += 3) {
        // Check array bounds
        if (i + 2 >= indices.size()) break;
        
        const unsigned int i0 = indices[i];
        const unsigned int i1 = indices[i+1];
        const unsigned int i2 = indices[i+2];
        
        // Validate indices
        if (i0 >= vertices.size() || i1 >= vertices.size() || i2 >= vertices.size()) {
            std::cerr << "Invalid vertex index in face data!" << std::endl;
            continue;
        }
        
        const auto& v0 = vertices[i0];
        const auto& v1 = vertices[i1];
        const auto& v2 = vertices[i2];
        
        triangleMesh->addTriangle(
            btVector3(v0.x, v0.y, v0.z),
            btVector3(v1.x, v1.y, v1.z),
            btVector3(v2.x, v2.y, v2.z)
        );
    }

    // Create collision shape
    collisionShape = new btBvhTriangleMeshShape(triangleMesh, true);
}

void Collision::createRigidBody() {

    // Create motion state
    btTransform startTransform;
    startTransform.setIdentity();
    auto position = globalTransform->getPosition();
    startTransform.setOrigin(btVector3(
        position.x,
        position.y,
        position.z
    ));
    
    motionState = new btDefaultMotionState(startTransform);

    // Create rigid body
    btRigidBody::btRigidBodyConstructionInfo rbInfo(
        0.0f, // Mass (0 = static)
        motionState,
        collisionShape,
        btVector3(0, 0, 0)
    );
    
    rigidBody = new btRigidBody(rbInfo);
    rigidBody->setFriction(1.0f);
    rigidBody->setRestitution(0.1f);
}

void Collision::setGlobalTransform(Transform& transform) {
    if(!isActive) return;
    if(!motionState) return;
    if(!rigidBody) return;
    if(!collisionShape) return;

    // Decomponi la matrice
    glm::mat4 mat = transform.getTransform();
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;

    glm::decompose(mat, scale, rotation, translation, skew, perspective);
    
    // Crea il nuovo btTransform
    btTransform bulletTransform;
    bulletTransform.setOrigin(btVector3(translation.x, translation.y, translation.z));
    bulletTransform.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));

    // Aggiorna motion state e rigid body
    motionState->setWorldTransform(bulletTransform);
    rigidBody->setWorldTransform(bulletTransform);
    collisionShape->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
}
