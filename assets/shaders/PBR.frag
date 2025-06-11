#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos; 
layout(location = 1) in vec3 fragNorm; 
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) in vec4 lightSpacePos;
layout(location = 4) in vec3 fragTangent;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform UniformBufferObject {
    mat4 mvpMat;
    mat4 mMat;
    mat4 nMat;
    mat4 lightSpaceMatrix;
    int tilingFactor;
    float opacity;
} ubo;

#define MAX_LIGHTS 40
#define SAMPLE_COUNT 2
layout(binding = 1) uniform GlobalUniformBufferObject {
    vec3 lightDir[MAX_LIGHTS];
    vec4 lightColor[MAX_LIGHTS];

    vec3 lightPosPoint[MAX_LIGHTS];
    vec4 lightColorPoint[MAX_LIGHTS];

    vec3 eyePos;
    int numLightsDir;
    int numLightsPoint;
} gubo;

layout(binding = 2) uniform samplerCube hdrEnvMap;
layout(binding = 3) uniform sampler2D shadowMap;
layout(binding = 4) uniform sampler2D textAlbedo;
layout(binding = 5) uniform sampler2D textRoughness;
layout(binding = 6) uniform sampler2D textMetallic;
layout(binding = 7) uniform sampler2D textNormal;
layout(binding = 8) uniform sampler2D textAO;

const float PI = 3.14159265359;

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
    return a2 / max(denom, 0.0001);
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;
    return NdotV / (NdotV * (1.0 - k) + k);
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV, roughness);
    float ggx2 = GeometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}

vec3 CookTorranceBRDF(vec3 albedo, vec3 N, vec3 V, vec3 L, float roughness, float metallic, float shadow) {
    vec3 H = normalize(V + L);
    vec3 F0 = mix(vec3(0.04), albedo, metallic);
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
    float NDF = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);
    vec3 specular = (NDF * G * F) / max(4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0), 0.0001);
    vec3 kd = mix(vec3(1.0) - F, vec3(0.0), metallic);
    vec3 diffuse = kd * albedo / PI;
    float NdotL = max(dot(N, L), 0.05);
    vec3 finalColor = (diffuse + specular) * NdotL;

    if(shadow > 0.0 && ubo.opacity > 0.9) {

        shadow /= pow(float(SAMPLE_COUNT + 1), 2.0);
        finalColor *= (1.0 - shadow);
    }
    return finalColor;
}

vec3 CookTorranceBRDFPoint(vec3 albedo, vec3 N, vec3 V, vec3 L, float roughness, float metallic) {
    vec3 H = normalize(V + L);
    vec3 F0 = mix(vec3(0.04), albedo, metallic);
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
    float NDF = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);
    vec3 specular = (NDF * G * F) / max(4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0), 0.0001);
    vec3 kd = mix(vec3(1.0) - F, vec3(0.0), metallic);
    vec3 diffuse = kd * albedo / PI;
    float NdotL = max(dot(N, L), 0.05);
    vec3 finalColor = (diffuse + specular) * NdotL;
    return finalColor;
}

vec3 reflectColor(vec3 viewDir, vec3 normal) {
    vec3 R = reflect(viewDir, normal);
    return texture(hdrEnvMap, R).rgb;
}

void main() {

    // Adjust texture coordinates for tiling
    vec2 tiledTexCoord = fragTexCoord * ubo.tilingFactor;

    // Sample textures with tiled coordinates
    vec3 albedo = texture(textAlbedo, tiledTexCoord).rgb;
    float roughness = texture(textRoughness, tiledTexCoord).r;
    float metallic = texture(textMetallic, tiledTexCoord).r;
    vec3 normalMap = texture(textNormal, tiledTexCoord).rgb * 2.0 - 1.0;
    normalMap.y = -normalMap.y;
    float ao = texture(textAO, tiledTexCoord).r;
    albedo *= ao; // Modifica dell'albedo in base all'ambient occlusion

    vec3 T = normalize(fragTangent);
    vec3 N = normalize(fragNorm);
    vec3 B = cross(N, T) * (gl_FrontFacing ? 1.0 : -1.0); // Correzione winding order
    mat3 TBN = mat3(T, B, N);
    N = normalize(TBN * normalMap); // Applicazione della normal map

    vec3 V = normalize(gubo.eyePos - fragPos);
    vec3 finalColor = vec3(0.0);

    vec3 reflected = reflectColor(V, N);
    vec3 F0 = mix(vec3(0.04), albedo, metallic);
    vec3 F = fresnelSchlick(max(dot(N, V), 0.0), F0);
    float reflectionStrength = pow(1.0 - roughness, 4.0) * 0.15;
    albedo = mix(albedo, reflected, reflectionStrength);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0); 
    vec2 shadowMapCoord = (lightSpacePos.xy / lightSpacePos.w) * 0.5 + 0.5;

    // Loop through multiple samples
    for (int i = -SAMPLE_COUNT / 2; i <= SAMPLE_COUNT / 2; ++i) {
        for (int j = -SAMPLE_COUNT / 2; j <= SAMPLE_COUNT / 2; ++j) {
            vec2 offset = vec2(i, j) * texelSize;
            vec2 shadowCoord = shadowMapCoord + offset;
            float depthInShadowMap = texture(shadowMap, shadowCoord).r + 0.32;

            // Perform the depth comparison
            float currentDepth = (lightSpacePos.z / lightSpacePos.w);
            if (currentDepth > depthInShadowMap) {
                shadow += 1.0; // Add contribution from this sample
            } else {
                shadow += 0.0; // No shadow
            }
        }
    }

    for (int i = 0; i < gubo.numLightsDir; i++) {
        vec3 L = normalize(gubo.lightDir[i]);
        vec3 LC = gubo.lightColor[i].rgb * gubo.lightColor[i].a;
        finalColor += CookTorranceBRDF(albedo, N, V, L, roughness, metallic, shadow) * LC;
    }

    for (int i = 0; i < gubo.numLightsPoint; i++) {
        vec3 lightPos = gubo.lightPosPoint[i];
        vec3 L = normalize(lightPos - fragPos);
        vec3 LC = gubo.lightColorPoint[i].rgb * gubo.lightColorPoint[i].a;
        float distance = length(lightPos - fragPos);
        float attenuation = 5.0 / (distance * distance);
        finalColor += CookTorranceBRDFPoint(albedo, N, V, L, roughness, metallic) * LC * attenuation;
    }

    // Metallic materials
    if (metallic > 0.8) {
        F0 = mix(vec3(0.04), albedo, metallic);
        vec3 F_env = fresnelSchlick(max(dot(N, V), 0.0), F0);
        float reflectionStrength = pow(1.0 - roughness, 4.0) * 1.0;
        vec3 envSpecular = reflected * F_env * reflectionStrength;
        finalColor += (gubo.lightColor[0].a / 40) * envSpecular;
    }

    // indirect lighting
    vec3 indirectDiffuse = texture(hdrEnvMap, normalMap).rgb;
    vec3 kd = mix(vec3(1.0) - F, vec3(0.0), metallic);
    vec3 indirectLight = kd * albedo * indirectDiffuse;
    indirectLight *= ao;
    finalColor += (gubo.lightColor[0].a / 40) * indirectLight;


    float opacity_albedo = texture(textAlbedo, tiledTexCoord).a;
    float finalOpacity = ubo.opacity * opacity_albedo;

    outColor = vec4(finalColor, finalOpacity);
}