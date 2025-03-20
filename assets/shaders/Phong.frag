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

layout(binding = 3) uniform sampler2D textDiffuse;

vec3 direct_light_dir(int i) {
	return gubo.lightDir[i];
}

vec3 direct_light_color(int i) {
	return gubo.lightColor[i].rgb;
}

vec3 point_light_dir(vec3 pos, int i) {
	return normalize(gubo.lightPosPoint[i] - pos);
}

vec3 point_light_color(vec3 pos, int i) {
	return pow(gubo.lightColorPoint[i].a / length(gubo.lightPosPoint[i] - pos), 2.0) * gubo.lightColorPoint[i].rgb;
}


vec3 BRDF(vec3 Albedo, vec3 Norm, vec3 EyeDir, vec3 LD) {

	// Phong BRDF components
	float diff = max(dot(Norm, LD), 0.0);
	vec3 Diffuse = Albedo * diff;

	// Specular component (Phong model)
	vec3 ReflectDir = reflect(-LD, Norm);
	float spec = pow(max(dot(EyeDir, ReflectDir), 0.0), 5.0); // Shininess = 5
	vec3 Specular = vec3(0.05) * spec; // 30% white specular light

	return Diffuse + Specular;
}

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos - fragPos);
	vec3 Albedo = texture(textDiffuse, fragTexCoord).rgb;

	vec3 LD;	// light direction
	vec3 LC;	// light color

	vec3 RendEqSol = vec3(0);

	for (int i = 0; i < gubo.numLightsDir; i++) {
		LD = direct_light_dir(i);
		LC = direct_light_color(i);
		RendEqSol += BRDF(Albedo, Norm, EyeDir, LD) * LC;
	}

	for (int i = 0; i < gubo.numLightsPoint; i++) {
		LD = point_light_dir(fragPos, i);
		LC = point_light_color(fragPos, i);
		RendEqSol += BRDF(Albedo, Norm, EyeDir, LD) * LC;
	}
	
	// Output color
	outColor = vec4(RendEqSol, 1.0f);
}