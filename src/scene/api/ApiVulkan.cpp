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
	alignas(16) glm::mat4 lightSpaceMatrix;
	alignas(4) int tilingFactor;
	alignas(4) float opacity;
};

struct GlobalUniformBufferObject
{
	// Directional light
	struct
	{
		alignas(16) glm::vec3 v;
	} lightDir[MAX_LIGHTS];
	alignas(16) glm::vec4 lightColor[MAX_LIGHTS];

	// Point light
	struct
	{
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
	glm::vec4 tan;
};

class VulkanApp : public BaseProject
{
private:
	Scene *scene;
	bool compute_shadows = true;

public:
	VulkanApp(Scene *scene, bool compute_shadows) : BaseProject()
	{
		this->scene = scene;
		this->compute_shadows = compute_shadows;
	}

protected:
	// Vertex formats
	VertexDescriptor VD;

	// Pipelines [Shader couples]
	Pipeline P;
	Pipeline P_background;
	Pipeline P_shadows;

	// Descriptor Layouts ["classes" of what will be passed to the shaders]
	DescriptorSetLayout DSL_P;
	DescriptorSetLayout DSL_P_background;
	DescriptorSetLayout DSL_P_shadows;

	// Models, textures and Descriptors (values assigned to the uniforms)
	// Please note that Model objects depends on the corresponding vertex structure
	// Models
	std::vector<Model<Vertex>> M;
	std::vector<std::shared_ptr<Mesh>> meshesVulkan;
	Model<Vertex> M_background;

	// Lights
	std::vector<std::shared_ptr<Light>> lights;
	std::vector<glm::mat4> trans_lights;
	int curr_light = 0;

	// Descriptor sets
	std::vector<DescriptorSet> DS_P;
	std::vector<DescriptorSet> DS_P_shadows;
	DescriptorSet DS_P_background;

	// Textures
	std::map<std::string, std::vector<TextureVulkan>> textures_map;
	std::vector<std::string> materials_name;
	std::vector<int> materials_tiling;
	std::vector<float> materials_opacity;
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
		initialBackgroundColor = {0.0f, 0.0f, 0.0f, 1.0f};

		// Descriptor pool sizes
		// uniformBlocksInPool = 15 * 2 + 2;
		// texturesInPool = 100;
		// setsInPool = 15 + 1 + 1;

		uniformBlocksInPool = 500;
		texturesInPool = 500;
		setsInPool = 500;

		Ar = 4.0f / 3.0f;
	}

	// What to do when the window changes size
	void onWindowResize(int w, int h)
	{
		std::cout << "Window resized to: " << w << " x " << h << "\n";

		if (w == 0 || h == 0)
		{
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
		B.resize(4 + num_textures);
		B[0] = {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS};
		B[1] = {1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS};
		B[2] = {2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT};
		B[3] = {3, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT};
		for (int i = 0; i < num_textures; i++)
		{
			B[i + 4] = {static_cast<uint32_t>(4 + i), VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT};
		}
		DSL_P.init(this, B);

		std::vector<DescriptorSetLayoutBinding> B_background;
		B_background.resize(2);
		B_background[0] = {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS};
		B_background[1] = {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT};
		DSL_P_background.init(this, B_background);

		// Descriptor Layouts P_shadows
		std::vector<DescriptorSetLayoutBinding> B_shadows;
		B_shadows.resize(1);
		B_shadows[0] = {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS};
		DSL_P_shadows.init(this, B_shadows);

		// Vertex descriptors
		VD.init(this,
						{{0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX}},
						{{0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos), sizeof(glm::vec3), POSITION},
						 {0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, UV), sizeof(glm::vec2), UV},
						 {0, 2, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, norm), sizeof(glm::vec3), NORMAL},
						 {0, 3, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(Vertex, tan), sizeof(glm::vec4), TANGENT}});

		// Pipelines [Shader couples]
		P.init(this, &VD, this->scene->getShader().getVertexPath(), this->scene->getShader().getFragmentPath(), {&DSL_P});
		P.setAdvancedFeatures(VK_COMPARE_OP_LESS_OR_EQUAL, VK_POLYGON_MODE_FILL,
													VK_CULL_MODE_NONE, true);

		P_background.init(this, &VD, "shaders/hdriVert.spv", "shaders/hdriFrag.spv", {&DSL_P_background});
		P_background.setAdvancedFeatures(VK_COMPARE_OP_LESS_OR_EQUAL, VK_POLYGON_MODE_FILL,
																		 VK_CULL_MODE_NONE, false);

		P_shadows.init(this, &VD, "shaders/shadowsVert.spv", "shaders/shadowsFrag.spv", {&DSL_P_shadows});
		P_shadows.setAdvancedFeatures(VK_COMPARE_OP_LESS_OR_EQUAL, VK_POLYGON_MODE_FILL, VK_CULL_MODE_BACK_BIT, false);

		// Models, textures and Descriptors (values assigned to the uniforms)
		auto root = this->scene->getRoot();
		meshesVulkan = root->getRecursiveMeshesTransform();

		// allocate the models
		M.resize(meshesVulkan.size());
		DS_P.resize(meshesVulkan.size());
		DS_P_shadows.resize(meshesVulkan.size());
		materials_name.resize(meshesVulkan.size());
		materials_tiling.resize(meshesVulkan.size());
		materials_opacity.resize(meshesVulkan.size());

		for (int i = 0; i < meshesVulkan.size(); i++)
		{
			// load mesh
			std::shared_ptr<Mesh> mesh = meshesVulkan[i];

			auto filename = mesh->getFilename();
			auto extension = filename.substr(filename.find_last_of(".") + 1);
			if (extension == "obj")
			{
				M[i].init(this, &VD, mesh->getFilename(), OBJ);
			}
			else
			{
				M[i].init(this, &VD, mesh->getFilename(), GLTF);
			}

			// load material and textures
			auto material = mesh->getMaterial();
			std::string material_name = material->getClassName();
			static const std::unordered_set<std::string> invalid_materials = {
					"BasicMaterial",
					"PBRMaterial",
					"Material"};

			if (invalid_materials.find(material_name) != invalid_materials.end())
			{
				std::cout << "Material \"" << material_name << "\" not accepted! Derive the material and ovveride the getClassName().\n";
				throw std::runtime_error("Material not accepted");
			}

			materials_name[i] = material_name;
			materials_tiling[i] = material->getTilingFactor();
			materials_opacity[i] = material->getOpacity();

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

		// load shadow texture
		if (!compute_shadows)
		{
			texture_shadow.init(this, "light_0.png");
		}

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
		P_shadows.create();
		P_background.create();

		// Models, textures and Descriptors (values assigned to the uniforms)
		for (int i = 0; i < DS_P.size(); i++)
		{
			std::string material = materials_name[i];
			std::vector<TextureVulkan> textures = textures_map[material];

			std::vector<DescriptorSetElement> E;
			E.resize(4 + textures.size());
			E[0] = {0, UNIFORM, sizeof(UniformBufferObject), nullptr};
			E[1] = {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr};
			E[2] = {2, TEXTURE, 0, &textures_hdri};
			E[3] = {3, TEXTURE, 0, &texture_shadow};
			for (int j = 0; j < textures.size(); j++)
			{
				E[j + 4] = {j + 4, TEXTURE, 0, &textures[j]};
			}
			DS_P[i].init(this, &DSL_P, E);
		}

		DS_P_background.init(this, &DSL_P_background, {{0, UNIFORM, sizeof(UniformBufferObject), nullptr}, {1, TEXTURE, 0, &textures_hdri}});

		// Models, textures and Descriptors (values assigned to the uniforms)
		for (int i = 0; i < DS_P_shadows.size(); i++)
		{
			std::vector<DescriptorSetElement> E;
			E.resize(1);
			E[0] = {0, UNIFORM, sizeof(UniformBufferObject), nullptr};
			DS_P_shadows[i].init(this, &DSL_P_shadows, E);
		}
	}

	// Here it is the creation of the command buffer:
	// You send to the GPU all the objects you want to draw,
	// with their buffers and textures

	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage)
	{

		if (compute_shadows) {
			P_shadows.bind(commandBuffer);
			for (int i = 0; i < M.size(); i++)
			{
				M[i].bind(commandBuffer);
				DS_P_shadows[i].bind(commandBuffer, P_shadows, 0, currentImage);

				vkCmdDrawIndexed(commandBuffer,
												static_cast<uint32_t>(M[i].indices.size()), 1, 0, 0, 0);
			}
		} else {

			P_background.bind(commandBuffer);
			M_background.bind(commandBuffer);
			DS_P_background.bind(commandBuffer, P_background, 0, currentImage);
			vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(M_background.indices.size()), 1, 0, 0, 0);

			P.bind(commandBuffer);
			for (int i = 0; i < M.size(); i++)
			{
				M[i].bind(commandBuffer);
				DS_P[i].bind(commandBuffer, P, 0, currentImage);

				vkCmdDrawIndexed(commandBuffer,
												 static_cast<uint32_t>(M[i].indices.size()), 1, 0, 0, 0);
			}
		
		}

	}

	// Here is where you update the uniforms.
	// Very likely this will be where you will be writing the logic of your application.
	void updateUniformBuffer(uint32_t currentImage)
	{
		static int frame = 0;
		if (compute_shadows)
			frame++;

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
				gubo.lightDir[numDir].v.y = -gubo.lightDir[numDir].v.y;
				gubo.lightColor[numDir] = glm::vec4(lights[i]->getColor(), lights[i]->getIntensity());
				numDir++;
				break;

			case TypeLight::POINT_LIGHT:
				gubo.lightPosPoint[numPoint].v = lights[i]->getPosition();
				gubo.lightPosPoint[numPoint].v.y = -gubo.lightPosPoint[numPoint].v.y;
				gubo.lightColorPoint[numPoint] = glm::vec4(lights[i]->getColor(), lights[i]->getIntensity());
				numPoint++;
				break;
			}
		}
		gubo.numLightsDir = numDir;
		gubo.numLightsPoint = numPoint;
		gubo.eyePos = cam->getPosition();

		// Create view matrix
		glm::vec3 lightPos = lights[curr_light]->getPosition();
		glm::vec3 lightDir = lights[curr_light]->getDirection();
		float yaw = atan2(lightDir.z, lightDir.x);
		float pitch = asin(lightDir.y);
		float roll = 0.0f;

		glm::mat4 lightView = glm::rotate(glm::mat4(1.0), -pitch, glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0), -yaw, glm::vec3(0, 1, 0)) * glm::translate(glm::mat4(1.0), -lightPos);

		// Final light-space matrix
		glm::mat4 M_light = glm::perspective(glm::radians(45.0f), Ar, 4.1f, 8.0f);
		M_light[1][1] *= -1;
		glm::mat4 lightSpaceMatrix = M_light * lightView;

		// scale the background by 100
		glm::mat4 trans_mat_background = glm::scale(glm::mat4(1.0f), glm::vec3(10000.0f));
		ubo.mMat = trans_mat_background;
		ubo.mvpMat = ViewPrj * ubo.mMat;
		ubo.nMat = glm::inverse(glm::transpose(ubo.mMat));
		ubo.lightSpaceMatrix = lightSpaceMatrix;
		ubo.tilingFactor = 1;
		ubo.opacity = 1.0f;
		DS_P_background.map(currentImage, &ubo, sizeof(ubo), 0);

		glm::mat4 AxTr = glm::scale(glm::mat4(1.0f), glm::vec3(0.0f));
		for (int i = 0; i < DS_P.size(); i++)
		{
			ubo.mMat = meshesVulkan[i]->getGlobalTransform().getTransform();
			ubo.mvpMat = ViewPrj * ubo.mMat;
			ubo.nMat = glm::inverse(glm::transpose(ubo.mMat));
			ubo.lightSpaceMatrix = lightSpaceMatrix * ubo.mMat;
			ubo.tilingFactor = materials_tiling[i];
			ubo.opacity = materials_opacity[i];
			DS_P[i].map(currentImage, &ubo, sizeof(ubo), 0);
			DS_P[i].map(currentImage, &gubo, sizeof(gubo), 1);


			if (compute_shadows)
			{
				ubo.mvpMat = lightSpaceMatrix * ubo.mMat;
				ubo.nMat = glm::inverse(glm::transpose(ubo.mMat));
				ubo.lightSpaceMatrix = lightSpaceMatrix * ubo.mMat;
				ubo.tilingFactor = 1;
				DS_P_shadows[i].map(currentImage, &ubo, sizeof(ubo), 0);
			}
		}

		if (compute_shadows && frame > 5)
		{
			saveScreenshot(("light_" + std::to_string(curr_light) + ".png").c_str(), currentImage);
			curr_light++;
			frame = 0;

			if (curr_light == lights.size())
			{
				exit(0);
			}
			
		}
		
	}

	// Here you destroy your pipelines and Descriptor Sets!
	// All the object classes defined in Starter.hpp have a method .cleanup() for this purpose
	void pipelinesAndDescriptorSetsCleanup()
	{
		// Cleanup pipelines
		P.cleanup();
		P_background.cleanup();
		P_shadows.cleanup();

		// Cleanup datasets
		for (int i = 0; i < DS_P.size(); i++)
			DS_P[i].cleanup();

		for (int i = 0; i < DS_P_shadows.size(); i++)
			DS_P_shadows[i].cleanup();

		DS_P_background.cleanup();
	}

	// Here you destroy all the Models, TextureVulkan and Desc. Set Layouts you created!
	// All the object classes defined in Starter.hpp have a method .cleanup() for this purpose
	// You also have to destroy the pipelines: since they need to be rebuilt, they have two different
	// methods: .cleanup() recreates them, while .destroy() delete them completely
	void localCleanup()
	{
		// Cleanup textures
		for (auto it = textures_map.begin(); it != textures_map.end(); ++it)
		{
			for (int j = 0; j < it->second.size(); j++)
			{
				it->second[j].cleanup();
			}
			textures_map[it->first].clear();
		}
		textures_map.clear();
		textures_hdri.cleanup();

		// Cleanup models
		for (int i = 0; i < M.size(); i++)
			M[i].cleanup();
		M.clear();

		M_background.cleanup();

		// Cleanup descriptor set layouts
		DSL_P.cleanup();
		DSL_P_background.cleanup();
		DSL_P_shadows.cleanup();

		// Destroies the pipelines
		P.destroy();
		P_shadows.destroy();
		P_background.destroy();
	}
};

ApiVulkan::ApiVulkan(Scene *scene, bool compute_shadows) : scene(scene)
{
	VulkanApp app(scene, compute_shadows);
	app.run();
}