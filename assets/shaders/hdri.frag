#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPosOut;
layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform UniformBufferObject {
    mat4 mvpMat;
    mat4 mMat;
    mat4 nMat;
    mat4 lightSpaceMatrix;
    int tilingFactor;
} ubo;

layout(binding = 1) uniform samplerCube hdrEnvMap;
layout(binding = 2) uniform samplerCube hdrEnvMapNight;

void main() {
    vec3 viewDir = normalize(fragPosOut);
    if (ubo.tilingFactor == 0) {
        outColor = texture(hdrEnvMapNight, viewDir);
    } else {
        outColor = texture(hdrEnvMap, viewDir);
    }
}
