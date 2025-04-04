#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;  // Vertex position
layout(location = 1) in vec3 fragNorm; // Vertex normal (non necessario per questo caso)

layout(location = 0) out vec3 fragPosOut; // Output fragment position

layout(binding = 0) uniform UniformBufferObject {
    mat4 mvpMat; // Model-View-Projection matrix
    mat4 mMat;   // Model matrix (non necessario per questo caso)
    mat4 nMat;   // Normal matrix (non necessario per questo caso)
    mat4 lightSpaceMatrix; // Light space matrix (non necessario per questo caso)
} ubo;

void main() {
    // Pass position to the fragment shader
    fragPosOut = fragPos;

    // Apply the MVP transformation
    gl_Position = ubo.mvpMat * vec4(fragPos, 1.0);
}
