#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPosOut;  // Incoming fragment position

layout(location = 0) out vec4 outColor; // Final output color

layout(binding = 1) uniform samplerCube hdrEnvMap; // HDR environment map

void main() {
    // Sample the HDR environment map based on the fragment position direction
    vec3 viewDir = normalize(fragPosOut); // View direction (since it's a skybox, use the fragment position)
    vec4 envColor = texture(hdrEnvMap, viewDir); // Sample the cube map using the view direction

    // Output the final color (HDR lighting information)
    outColor = envColor; // Use the environment color directly without any lighting calculations
}
