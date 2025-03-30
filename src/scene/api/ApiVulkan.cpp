#include "scene/api/ApiVulkan.hpp"
#include "scene/Scene.hpp"
#include "lights/Light.hpp"
#include "StarterVulkan.hpp"
#include <unordered_set>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform2.hpp>
#define MAX_LIGHTS 20

struct UniformBufferObject
{
	alignas(16) glm::mat4 mvpMat;
	alignas(16) glm::mat4 mMat;
	alignas(16) glm::mat4 nMat;
};

struct GlobalUniformBufferObject
{
	// Directional light
	struct {
		alignas(16) glm::vec3 v;
	} lightDir[MAX_LIGHTS];
	alignas(16) glm::vec4 lightColor[MAX_LIGHTS];


	// Point light
	struct {
		alignas(16) glm::vec3 v;
	} lightPosPoint[MAX_LIGHTS];
	alignas(16) glm::vec4 lightColorPoint[MAX_LIGHTS];


	alignas(16) glm::vec3 eyePos;
	alignas(4) int numLightsDir;
	alignas(4) int numLightsPoint;
};

// The vertices data structures
struct Vertex
{
	glm::vec3 pos;
	glm::vec2 UV;
	glm::vec3 norm;
};

class VulkanApp : public BaseProject
{
private:
	Scene *scene;

public:
	VulkanApp(Scene *scene) : BaseProject()
	{
		this->scene = scene;
	}

protected:


	// Vertex formats
	VertexDescriptor VD;

	// Pipelines [Shader couples]
	Pipeline P;
	Pipeline P_background;

	// Descriptor Layouts ["classes" of what will be passed to the shaders]
	DescriptorSetLayout DSL_P;
	DescriptorSetLayout DSL_P_background;

	// Models, textures and Descriptors (values assigned to the uniforms)
	// Please note that Model objects depends on the corresponding vertex structure
	// Models
	std::vector<Model<Vertex>> M;
	std::vector<glm::mat4> trans_mat;
	Model<Vertex> M_background;

	// Lights
	std::vector<std::shared_ptr<Light>> lights;
	std::vector<glm::mat4> trans_lights;

	// Descriptor sets
	std::vector<DescriptorSet> DS_P;
	DescriptorSet DS_P_background;

	// Textures
	std::map<std::string, std::vector<TextureVulkan>> textures_map;
	std::vector<std::string> materials_name;
	TextureVulkan textures_hdri;
	TextureVulkan texture_shadow;

	// Other application parameters
	float Ar;

	// Here you set the main application parameters
	void setWindowParameters()
	{
		// window size, titile and initial background
		windowWidth = 1024;
		windowHeight = 768;
		windowTitle = "VulkanApp - 3D Transformations";
		windowResizable = GLFW_TRUE;
		initialBackgroundColor = {0.0f, 0.005f, 0.01f, 1.0f};

		// Descriptor pool sizes
		// uniformBlocksInPool = 15 * 2 + 2;
		// texturesInPool = 100;
		// setsInPool = 15 + 1 + 1;

		uniformBlocksInPool = 200;
		texturesInPool = 200;
		setsInPool = 200;

		Ar = 4.0f / 3.0f;
	}

	// What to do when the window changes size
	void onWindowResize(int w, int h)
	{
		std::cout << "Window resized to: " << w << " x " << h << "\n";

		if (w == 0 || h == 0) {
			return;
		}

		Ar = (float)w / (float)h;
	}

	// Here you load and setup all your Vulkan Models and Texutures.
	// Here you also create your Descriptor set layouts and load the shaders for the pipelines
	void localInit()
	{
		auto texture_types = this->scene->getShader().getTextureTypes();
		int num_textures = texture_types.size();

		// Descriptor Layouts P
		std::vector<DescriptorSetLayoutBinding> B;
		B.resize(3 + num_textures);
		B[0] = {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS};
		B[1] = {1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS};
		B[2] = {2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT};
		for (int i = 0; i < num_textures; i++)
		{
			B[i+3] = {static_cast<uint32_t>(3 + i), VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT};
		}
		DSL_P.init(this, B);


		std::vector<DescriptorSetLayoutBinding> B_background;
		B_background.resize(2);
		B_background[0] = {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS};
		B_background[1] = {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT};
		DSL_P_background.init(this, B_background);


		// Vertex descriptors
		VD.init(this, 
			{{0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX}}, 
			{
				{0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos), sizeof(glm::vec3), POSITION}, 
				{0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, UV), sizeof(glm::vec2), UV}, 
				{0, 2, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, norm), sizeof(glm::vec3), NORMAL}
			});

		// Pipelines [Shader couples]
		P.init(this, &VD, this->scene->getShader().getVertexPath(), this->scene->getShader().getFragmentPath(), {&DSL_P});
		P.setAdvancedFeatures(VK_COMPARE_OP_LESS_OR_EQUAL, VK_POLYGON_MODE_FILL,
													VK_CULL_MODE_NONE, false);

		P_background.init(this, &VD, "shaders/hdriVert.spv", "shaders/hdriFrag.spv", {&DSL_P_background});
		P_background.setAdvancedFeatures(VK_COMPARE_OP_LESS_OR_EQUAL, VK_POLYGON_MODE_FILL,
													VK_CULL_MODE_NONE, false);

		// Models, textures and Descriptors (values assigned to the uniforms)
		auto root = this->scene->getRoot();
		auto meshes = root->getRecursiveMeshesTransform();
		
		// allocate the models
		M.resize(meshes.size());
		DS_P.resize(meshes.size());
		materials_name.resize(num_textures);

		for (int i = 0; i < meshes.size(); i++)
		{
			// load mesh
			std::shared_ptr<Mesh> mesh = meshes[i].first;
			M[i].init(this, &VD, mesh->getFilename(), OBJ);
			
			// apply transform
			trans_mat.push_back(meshes[i].second.getTransform());

			// load material and textures
			auto material = mesh->getMaterial();
			std::string material_name = material->getClassName();
			static const std::unordered_set<std::string> invalid_materials = {
				"BasicMaterial", 
				"PBRMaterial", 
				"Material"
		};
		
			if (invalid_materials.find(material_name) != invalid_materials.end()) {
					std::cout << "Material \"" << material_name << "\" not accepted! Derive the material and ovveride the getClassName().\n";
					throw std::runtime_error("Material not accepted");
			}


			materials_name[i] = material_name;
			
			auto it = textures_map.find(material_name);
			if (it == textures_map.end())
			{
				textures_map[material_name] = std::vector<TextureVulkan>();
				textures_map[material_name].resize(num_textures);
				for (int j = 0; j < num_textures; j++)
				{
					auto texture = material->getTexture(texture_types[j]);
					std::cout << "Loading texture: " << texture->getPath() << "\n";
					textures_map[material_name][j].init(this, texture->getPath().c_str());
				}
			}
			
		}

		M_background.init(this, &VD, "assets/models/hdri.obj", OBJ);
		auto textures_hdri_string = this->scene->getHDRI();
		textures_hdri.initCubic(this, textures_hdri_string.data());

		auto lights_current = root->getRecursiveLightsTransform();
		lights.resize(lights_current.size());
		trans_lights.resize(lights_current.size());

		for (int i = 0; i < lights_current.size(); i++)
		{
			lights[i] = lights_current[i].first;

			// apply transform
			trans_lights.push_back(lights_current[i].second.getTransform());
		}

	}

	// Here you create your pipelines and Descriptor Sets!
	void pipelinesAndDescriptorSetsInit()
	{
		// This creates a new pipeline (with the current surface), using its shaders
		P.create();
		P_background.create();

		// Models, textures and Descriptors (values assigned to the uniforms)
		for (int i = 0; i < DS_P.size(); i++)
		{
			std::string material = materials_name[i];
			std::vector<TextureVulkan> textures = textures_map[material];


			std::vector<DescriptorSetElement> E;
			E.resize(3 + textures.size());
			E[0] = {0, UNIFORM, sizeof(UniformBufferObject), nullptr};
			E[1] = {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr};
			E[2] = {2, TEXTURE, 0, &textures_hdri};
			for(int j = 0; j < textures.size(); j++)
			{
				E[j + 3] = {j + 3, TEXTURE, 0, &textures[j]};
			}
			DS_P[i].init(this, &DSL_P, E);
		}

		DS_P_background.init(this, &DSL_P_background, {
			{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
			{1, TEXTURE, 0, &textures_hdri}
		});
	}


	// Here it is the creation of the command buffer:
	// You send to the GPU all the objects you want to draw,
	// with their buffers and textures

	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage)
	{

		P.bind(commandBuffer);
		for (int i = 0; i < M.size(); i++)
		{
			M[i].bind(commandBuffer);
			DS_P[i].bind(commandBuffer, P, 0, currentImage);

			vkCmdDrawIndexed(commandBuffer,
											 static_cast<uint32_t>(M[i].indices.size()), 1, 0, 0, 0);
		}

		// binds the pipeline
		P_background.bind(commandBuffer);
		M_background.bind(commandBuffer);
		DS_P_background.bind(commandBuffer, P_background, 0, currentImage);
		vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(M_background.indices.size()), 1, 0, 0, 0);
	}

	// Here is where you update the uniforms.
	// Very likely this will be where you will be writing the logic of your application.
	void updateUniformBuffer(uint32_t currentImage)
	{
		scene->update();

		auto cam = scene->getCamera();

		glm::mat4 M = glm::perspective(glm::radians(45.0f), Ar, 0.1f, 100000.0f);
		M[1][1] *= -1;

		glm::mat4 Mv = cam->getViewMatrix();
		glm::mat4 ViewPrj = M * Mv;

		UniformBufferObject ubo{};

		// updates global uniforms
		GlobalUniformBufferObject gubo{};
		int numDir = 0;
		int numPoint = 0;
		for (int i = 0; i < lights.size(); i++)
		{
			switch (lights[i]->getType())
			{
				case TypeLight::DIRECTIONAL:
					gubo.lightDir[numDir].v = lights[i]->getDirection();
					gubo.lightColor[numDir] = glm::vec4(lights[i]->getColor(), lights[i]->getIntensity());
					numDir++;
					break;
			
				case TypeLight::POINT_LIGHT:
					gubo.lightPosPoint[numPoint].v = lights[i]->getPosition();
					gubo.lightColorPoint[numPoint] = glm::vec4(lights[i]->getColor(), lights[i]->getIntensity());
					numPoint++;
					break;
			}
			
		}
		gubo.numLightsDir = numDir;
		gubo.numLightsPoint = numPoint;
		gubo.eyePos = cam->getPosition();

		// scale the background by 100
		glm::mat4 trans_mat_background = glm::scale(glm::mat4(1.0f), glm::vec3(10000.0f));
		ubo.mMat = trans_mat_background;
		ubo.mvpMat = ViewPrj * ubo.mMat;
		ubo.nMat = glm::inverse(glm::transpose(ubo.mMat));
		DS_P_background.map(currentImage, &ubo, sizeof(ubo), 0);

		glm::mat4 AxTr = glm::scale(glm::mat4(1.0f), glm::vec3(0.0f));
		for (int i = 0; i < DS_P.size(); i++)
		{
			ubo.mMat = trans_mat[i];
			ubo.mvpMat = ViewPrj * ubo.mMat;
			ubo.nMat = glm::inverse(glm::transpose(ubo.mMat));
			DS_P[i].map(currentImage, &ubo, sizeof(ubo), 0);
			DS_P[i].map(currentImage, &gubo, sizeof(gubo), 1);
		}
	}


	// Here you destroy your pipelines and Descriptor Sets!
	// All the object classes defined in Starter.hpp have a method .cleanup() for this purpose
	void pipelinesAndDescriptorSetsCleanup()
	{
		P.create();
		P_background.create();

		DS_P.resize(M.size());

		for (int i = 0; i < (int)M.size(); i++)
		{
			std::vector<DescriptorSetElement> E;
			E.resize(3 + textures[i].size());

			E[0] = {0, UNIFORM,  sizeof(UniformBufferObject),       nullptr};
			E[1] = {1, UNIFORM,  sizeof(GlobalUniformBufferObject), nullptr};

			E[2] = {2, TEXTURE,  0, &textures_hdri};

			for (int j = 0; j < (int)textures[i].size(); j++)
			{
				E[j + 3] = {
					static_cast<int32_t>(j + 3),
					TEXTURE,
					0,
					&textures[i][j]
				};
			}

			DS_P[i].init(this, &DSL_P, E);
		}

		DS_P_background.init(this, &DSL_P_background, {
			{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
			{1, TEXTURE, 0, &textures_hdri}
		});
	}

	// Here you destroy all the Models, TextureVulkan and Desc. Set Layouts you created!
	// All the object classes defined in Starter.hpp have a method .cleanup() for this purpose
	// You also have to destroy the pipelines: since they need to be rebuilt, they have two different
	// methods: .cleanup() recreates them, while .destroy() delete them completely
	void localCleanup()
	{
		// Cleanup textures
		for(auto it = textures_map.begin(); it != textures_map.end(); ++it)
		{
			for (int j = 0; j < it->second.size(); j++)
			{
				it->second[j].cleanup();
			}
			textures_map[it->first].clear();
		}
		textures_hdri.cleanup();

		// Cleanup models
		for (int i = 0; i < M.size(); i++)
			M[i].cleanup();
		M.clear();

		M_background.cleanup();

		// Cleanup descriptor set layouts
		DSL_P.cleanup();

		// Destroies the pipelines
		P.destroy();
		P_background.destroy();
	}
};

ApiVulkan::ApiVulkan(Scene *scene) : scene(scene)
{
	VulkanApp app(scene);
	app.run();
}