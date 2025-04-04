#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 mvpMat;
    mat4 mMat;
    mat4 nMat;
    mat4 lightSpaceMatrix;
} ubo;

layout(location = 0) in vec3 inPosition; // Input vertex position

void main() {
    // Transform the vertex position to light space
    gl_Position = ubo.lightSpaceMatrix * vec4(inPosition, 1.0);
}
