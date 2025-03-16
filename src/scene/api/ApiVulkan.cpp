#include "scene/api/ApiVulkan.hpp"
#include "scene/Scene.hpp"
#include "StarterVulkan.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform2.hpp>

// The uniform buffer object used in this example
struct UniformBufferObject
{
	alignas(16) glm::mat4 mvpMat;
	alignas(16) glm::mat4 mMat;
	alignas(16) glm::mat4 nMat;
	alignas(16) glm::vec4 overColor;
};

struct GlobalUniformBufferObject
{
	alignas(16) glm::vec3 lightDir;
	alignas(16) glm::vec4 lightColor;
	alignas(16) glm::vec3 eyePos;
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

	// Descriptor Layouts ["classes" of what will be passed to the shaders]
	DescriptorSetLayout DSL;

	// Vertex formats
	VertexDescriptor VD;

	// Pipelines [Shader couples]
	Pipeline P;

	// Models, textures and Descriptors (values assigned to the uniforms)
	// Please note that Model objects depends on the corresponding vertex structure
	// Models
	std::vector<Model<Vertex>> M;
	std::vector<glm::mat4> trans_mat;

	// Descriptor sets
	std::vector<DescriptorSet> DS;

	// Textures
	Texture T1, T2;

	// Other application parameters
	glm::vec3 CamPos = glm::vec3(0.0, 1.5, 7.0);
	float CamAlpha = 0.0f;
	float CamBeta = 0.0f;
	float Ar;

	// Here you set the main application parameters
	void setWindowParameters()
	{
		// window size, titile and initial background
		windowWidth = 800;
		windowHeight = 600;
		windowTitle = "VulkanApp - 3D Transformations";
		windowResizable = GLFW_TRUE;
		initialBackgroundColor = {0.0f, 0.005f, 0.01f, 1.0f};

		// Descriptor pool sizes
		uniformBlocksInPool = 15 * 2 + 2;
		texturesInPool = 15 + 1 + 1;
		setsInPool = 15 + 1 + 1;

		Ar = 4.0f / 3.0f;
	}

	// What to do when the window changes size
	void onWindowResize(int w, int h)
	{
		std::cout << "Window resized to: " << w << " x " << h << "\n";
		Ar = (float)w / (float)h;
	}

	// Here you load and setup all your Vulkan Models and Texutures.
	// Here you also create your Descriptor set layouts and load the shaders for the pipelines
	void localInit()
	{
		// Descriptor Layouts [what will be passed to the shaders]
		DSL.init(this, {{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS},
										{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT},
										{2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS}});

		// Vertex descriptors
		VD.init(this, {{0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX}}, {{0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos), sizeof(glm::vec3), POSITION}, {0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, UV), sizeof(glm::vec2), UV}, {0, 2, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, norm), sizeof(glm::vec3), NORMAL}});

		// Pipelines [Shader couples]
		P.init(this, &VD, "shaders/PhongVert.spv", "shaders/PhongFrag.spv", {&DSL});
		P.setAdvancedFeatures(VK_COMPARE_OP_LESS_OR_EQUAL, VK_POLYGON_MODE_FILL,
													VK_CULL_MODE_NONE, false);

		// Models, textures and Descriptors (values assigned to the uniforms)
		auto root = this->scene->getRoot();
		auto meshes = root->getRecursiveMeshesTransform();
		
		// allocate the models
		M.resize(meshes.size());
		DS.resize(meshes.size());

		for (int i = 0; i < meshes.size(); i++)
		{
			std::shared_ptr<Mesh> mesh = meshes[i].first;
			M[i].init(this, &VD, mesh->getFilename(), OBJ);
			trans_mat.push_back(meshes[i].second.getTransform());
		}

		// Create the textures
		T1.init(this, "assets/textures/Picasso.jpg");
		T2.init(this, "assets/textures/Textures.png");
	}

	// Here you create your pipelines and Descriptor Sets!
	void pipelinesAndDescriptorSetsInit()
	{
		// This creates a new pipeline (with the current surface), using its shaders
		P.create();

		// Models, textures and Descriptors (values assigned to the uniforms)
		for (int i = 0; i < DS.size(); i++)
		{
			DS[i].init(this, &DSL, {{0, UNIFORM, sizeof(UniformBufferObject), nullptr}, {1, TEXTURE, 0, &T1}, {2, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr}});
		}
	}


	// Here it is the creation of the command buffer:
	// You send to the GPU all the objects you want to draw,
	// with their buffers and textures

	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage)
	{
		// binds the pipeline
		P.bind(commandBuffer);

		for (int i = 0; i < M.size(); i++)
		{
			M[i].bind(commandBuffer);
			DS[i].bind(commandBuffer, P, 0, currentImage);

			vkCmdDrawIndexed(commandBuffer,
											 static_cast<uint32_t>(M[i].indices.size()), 1, 0, 0, 0);
		}
	}

	// Here is where you update the uniforms.
	// Very likely this will be where you will be writing the logic of your application.
	void updateUniformBuffer(uint32_t currentImage)
	{
		static bool debounce = false;
		static int curDebounce = 0;

		float deltaT;
		glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
		bool fire = false;
		getSixAxis(deltaT, m, r, fire);

		const float ROT_SPEED = glm::radians(120.0f);
		const float MOVE_SPEED = 2.0f;

		CamAlpha = CamAlpha - ROT_SPEED * deltaT * r.y;
		CamBeta = CamBeta - ROT_SPEED * deltaT * r.x;
		CamBeta = CamBeta < glm::radians(-90.0f) ? glm::radians(-90.0f) : (CamBeta > glm::radians(90.0f) ? glm::radians(90.0f) : CamBeta);

		glm::vec3 ux = glm::rotate(glm::mat4(1.0f), CamAlpha, glm::vec3(0, 1, 0)) * glm::vec4(1, 0, 0, 1);
		glm::vec3 uz = glm::rotate(glm::mat4(1.0f), CamAlpha, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1);
		CamPos = CamPos + MOVE_SPEED * m.x * ux * deltaT;
		CamPos = CamPos + MOVE_SPEED * m.y * glm::vec3(0, 1, 0) * deltaT;
		CamPos = CamPos + MOVE_SPEED * m.z * uz * deltaT;

		if (glfwGetKey(window, GLFW_KEY_SPACE))
		{
			if (!debounce)
			{
				debounce = true;
				curDebounce = GLFW_KEY_SPACE;

				if (!screenshotSaved)
				{
					saveScreenshot("VulkanApp.png", currentImage);
				}

				RebuildPipeline();
			}
		}
		else
		{
			if ((curDebounce == GLFW_KEY_SPACE) && debounce)
			{
				debounce = false;
				curDebounce = 0;
			}
		}

		// Standard procedure to quit when the ESC key is pressed
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		glm::mat4 M = glm::perspective(glm::radians(45.0f), Ar, 0.1f, 50.0f);
		M[1][1] *= -1;

		glm::mat4 Mv = glm::rotate(glm::mat4(1.0), -CamBeta, glm::vec3(1, 0, 0)) *
									 glm::rotate(glm::mat4(1.0), -CamAlpha, glm::vec3(0, 1, 0)) *
									 glm::translate(glm::mat4(1.0), -CamPos);

		glm::mat4 ViewPrj = M * Mv;
		UniformBufferObject ubo{};
		glm::mat4 baseTr = glm::mat4(1.0f);
		// Here is where you actually update your uniforms

		// updates global uniforms
		GlobalUniformBufferObject gubo{};
		gubo.lightDir = glm::vec3(cos(glm::radians(135.0f)), sin(glm::radians(135.0f)), 0.0f);
		gubo.lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		gubo.eyePos = CamPos;

		glm::mat4 AxTr = glm::scale(glm::mat4(1.0f), glm::vec3(0.0f));
		for (int i = 0; i < DS.size(); i++)
		{
			ubo.mMat = baseTr * trans_mat[i];
			ubo.mvpMat = ViewPrj * ubo.mMat;
			ubo.nMat = glm::inverse(glm::transpose(ubo.mMat));
			ubo.overColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
			DS[i].map(currentImage, &ubo, sizeof(ubo), 0);
			DS[i].map(currentImage, &gubo, sizeof(gubo), 2);
		}
		ubo.mMat = baseTr * AxTr * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ubo.mvpMat = ViewPrj * ubo.mMat;
		ubo.nMat = glm::inverse(glm::transpose(ubo.mMat));
	}


	// Here you destroy your pipelines and Descriptor Sets!
	// All the object classes defined in Starter.hpp have a method .cleanup() for this purpose
	void pipelinesAndDescriptorSetsCleanup()
	{
		// Cleanup pipelines
		P.cleanup();

		// Cleanup datasets
		for (int i = 0; i < DS.size(); i++)
			DS[i].cleanup();
		DS.clear();
	}

	// Here you destroy all the Models, Texture and Desc. Set Layouts you created!
	// All the object classes defined in Starter.hpp have a method .cleanup() for this purpose
	// You also have to destroy the pipelines: since they need to be rebuilt, they have two different
	// methods: .cleanup() recreates them, while .destroy() delete them completely
	void localCleanup()
	{
		// Cleanup textures
		T1.cleanup();
		T2.cleanup();

		// Cleanup models
		for (int i = 0; i < M.size(); i++)
			M[i].cleanup();
		M.clear();

		// Cleanup descriptor set layouts
		DSL.cleanup();

		// Destroies the pipelines
		P.destroy();
	}
};

ApiVulkan::ApiVulkan(Scene *scene) : scene(scene)
{
	VulkanApp app(scene);
	app.run();
}