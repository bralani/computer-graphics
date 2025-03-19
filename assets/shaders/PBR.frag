#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform UniformBufferObject {
    mat4 mvpMat;
    mat4 mMat;
    mat4 nMat;
} ubo;

#define MAX_LIGHTS 20
layout(binding = 1) uniform GlobalUniformBufferObject {
    vec3 lightDir[MAX_LIGHTS];
    vec4 lightColor[MAX_LIGHTS];

    vec3 lightPosPoint[MAX_LIGHTS];
    vec4 lightColorPoint[MAX_LIGHTS];

    vec3 eyePos;
    int numLightsDir;
    int numLightsPoint;
} gubo;

layout(binding = 2) uniform sampler2D textAlbedo;
layout(binding = 3) uniform sampler2D textRoughness;
layout(binding = 4) uniform sampler2D textMetallic;
layout(binding = 5) uniform sampler2D textNormal;
layout(binding = 6) uniform sampler2D textAO;

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

vec3 CookTorranceBRDF(vec3 albedo, vec3 N, vec3 V, vec3 L, float roughness, float metallic) {
    vec3 H = normalize(V + L);
    vec3 F0 = mix(vec3(0.04), albedo, metallic);
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
    float NDF = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);
    vec3 specular = (NDF * G * F) / max(4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0), 0.0001);
    vec3 kd = mix(vec3(1.0) - F, vec3(0.0), metallic);
    vec3 diffuse = kd * albedo / PI;
    float NdotL = max(dot(N, L), 0.0);
    return (diffuse + specular) * NdotL;
}

void main() {
    vec3 albedo = texture(textAlbedo, fragTexCoord).rgb;
    float roughness = texture(textRoughness, fragTexCoord).r;
    float metallic = texture(textMetallic, fragTexCoord).r;
    vec3 normalMap = texture(textNormal, fragTexCoord).rgb * 2.0 - 1.0;
    float ambientOcclusion = texture(textAO, fragTexCoord).r;

    // TBN matrix for normal map
    vec3 T = normalize(vec3(ubo.mMat * vec4(1.0, 0.0, 0.0, 0.0)));
    vec3 B = normalize(vec3(ubo.mMat * vec4(0.0, 1.0, 0.0, 0.0)));
    vec3 N = normalize(fragNorm);
    mat3 TBN = mat3(T, B, N);
    N = normalize(TBN * normalMap);

    vec3 V = normalize(gubo.eyePos - fragPos);
    vec3 finalColor = vec3(0.0);

    // Directional Lights
    for (int i = 0; i < gubo.numLightsDir; i++) {
        vec3 L = normalize(gubo.lightDir[i]);
        vec3 LC = gubo.lightColor[i].rgb * gubo.lightColor[i].a;
        finalColor += CookTorranceBRDF(albedo, N, V, L, roughness, metallic) * LC;
    }

    // Point Lights
    for (int i = 0; i < gubo.numLightsPoint; i++) {
        vec3 lightPos = gubo.lightPosPoint[i];
        vec3 L = normalize(lightPos - fragPos);
        vec3 LC = gubo.lightColorPoint[i].rgb * gubo.lightColorPoint[i].a;

        float distance = length(lightPos - fragPos);
        float attenuation = 1.0 / (distance * distance);

        finalColor += CookTorranceBRDF(albedo, N, V, L, roughness, metallic) * LC * attenuation;
    }

    // Ambient light simulation (Indirect light)
    vec3 ambientLight = vec3(0.1); // Basic ambient intensity
    finalColor += ambientLight * albedo * ambientOcclusion;

    // Output color
    outColor = vec4(finalColor, 1.0);
}