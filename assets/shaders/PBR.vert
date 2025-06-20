#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 mvpMat;
    mat4 mMat;
    mat4 nMat;
    mat4 lightSpaceMatrix;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 inNorm;
layout(location = 3) in vec4 inTangent;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec3 fragNorm;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) out vec4 lightSpacePos;
layout(location = 4) out vec3 fragTangent;


void main() {
    gl_Position = ubo.mvpMat * vec4(inPosition, 1.0);
    fragPos = (ubo.mMat * vec4(inPosition, 1.0)).xyz;
    fragNorm = mat3(ubo.nMat) * inNorm;
    fragTexCoord = inUV;
    fragTangent = mat3(ubo.mMat) * inTangent.xyz;
    fragTangent = normalize(fragTangent - dot(fragTangent, fragNorm) * fragNorm);
    
    // Compute the position in light space and normalize the coordinates
    lightSpacePos = ubo.lightSpaceMatrix * vec4(inPosition, 1.0);
}