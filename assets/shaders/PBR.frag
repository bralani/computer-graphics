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

layout(binding = 1) uniform GlobalUniformBufferObject {
	vec3 lightDir;
	vec4 lightColor;
	vec3 eyePos;
} gubo;

layout(binding = 2) uniform sampler2D textAlbedo;
layout(binding = 3) uniform sampler2D textRoughness;
layout(binding = 4) uniform sampler2D textMetallic;

const float PI = 3.14159265359;

// Fresnel-Schlick approximation
vec3 fresnelSchlick(float cosTheta, vec3 F0) {
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

// GGX/Trowbridge-Reitz normal distribution function (NDF)
float DistributionGGX(vec3 N, vec3 H, float roughness) {
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH * NdotH;
	
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return a2 / max(denom, 0.0001);
}

// Smith-Schlick approximation for Geometry function
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

// Cook-Torrance BRDF
vec3 CookTorranceBRDF(vec3 albedo, vec3 N, vec3 V, vec3 L, float roughness, float metallic) {
	vec3 H = normalize(V + L);

	// Fresnel Reflectance at normal incidence (Schlick’s Approximation)
	vec3 F0 = mix(vec3(0.04), albedo, metallic);
	vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

	// GGX Normal Distribution Function
	float NDF = DistributionGGX(N, H, roughness);

	// Smith’s Geometry Function
	float G = GeometrySmith(N, V, L, roughness);

	// Cook-Torrance Specular Term
	vec3 specular = (NDF * G * F) / max(4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0), 0.0001);

	// Lambertian Diffuse Term (only if non-metallic)
	vec3 kd = mix(vec3(1.0) - F, vec3(0.0), metallic);
	vec3 diffuse = kd * albedo / PI;

	// Final Rendering Equation
	float NdotL = max(dot(N, L), 0.0);
	return (diffuse + specular) * NdotL;
}

void main() {
	// Extract surface properties from textures
	vec3 albedo = texture(textAlbedo, fragTexCoord).rgb;
	float roughness = texture(textRoughness, fragTexCoord).r;
	float metallic = texture(textMetallic, fragTexCoord).r;

	vec3 N = normalize(fragNorm);
	vec3 V = normalize(gubo.eyePos - fragPos);
	vec3 L = normalize(gubo.lightDir);
	vec3 LC = gubo.lightColor.rgb;

	// Compute final color using the Cook-Torrance BRDF
	vec3 finalColor = CookTorranceBRDF(albedo, N, V, L, roughness, metallic) * LC;

	// Output final color
	outColor = vec4(finalColor, 1.0);
}