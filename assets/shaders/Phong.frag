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
	
layout(binding = 2) uniform sampler2D textDiffuse;

vec3 direct_light_dir(vec3 pos, int i) {
	return gubo.lightDir;
}

vec3 direct_light_color(vec3 pos, int i) {
	return gubo.lightColor.rgb;
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

	// Fourth light
	LD = direct_light_dir(fragPos, 3);
	LC = direct_light_color(fragPos, 3);
	RendEqSol += BRDF(Albedo, Norm, EyeDir, LD) * LC;
	
	// Output color
	outColor = vec4(RendEqSol, 1.0f);
}