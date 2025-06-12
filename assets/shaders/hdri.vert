#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 0) out vec3 fragPosOut;

layout(binding = 0) uniform UniformBufferObject {
    mat4 mvpMat; // Model-View-Projection matrix
    mat4 mMat;
    mat4 nMat;
    mat4 lightSpaceMatrix;
    int tilingFactor;
} ubo;

void main() {
    fragPosOut = fragPos;

    gl_Position = ubo.mvpMat * vec4(fragPos, 1.0);
}
