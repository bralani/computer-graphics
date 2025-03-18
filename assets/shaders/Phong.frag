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
layout(binding = 3) uniform sampler2D textDiffuse2;

vec3 direct_light_dir(vec3 pos, int i) {
	return gubo.lightDir;
}

vec3 direct_light_color(vec3 pos, int i) {
	return gubo.lightColor.rgb;
}


vec3 BRDF(vec3 Albedo, vec3 Norm, vec3 EyeDir, vec3 LD) {
// Compute the BRDF, with a given color <Albedo>, in a given position characterized bu a given normal vector <Norm>,
// for a light direct according to <LD>, and viewed from a direction <EyeDir>
	vec3 Diffuse;
	vec3 Specular;
	Diffuse = Albedo * max(dot(Norm, LD),0.0f);
	Specular = vec3(pow(max(dot(EyeDir, -reflect(LD, Norm)),0.0f), 160.0f));
	
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