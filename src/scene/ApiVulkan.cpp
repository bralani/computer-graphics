#include "StarterVulkan.hpp"
#include "scene/api/ApiVulkan.hpp"

// MAIN ! 
class VulkanApp : public BaseProject {
	private:
		glm::mat4 mm[15];
		bool mhil[15];
	public:
		void SetMatrix(int i, glm::mat4 M, bool hil) {
			if((i >= 0) && (i < 15)) {
				mm[i] = M;
				mhil[i] = hil;
			}
		}
	protected:
	
	glm::mat4 Tpre[15];

	// Descriptor Layouts ["classes" of what will be passed to the shaders]
	DescriptorSetLayout DSL;

	// Vertex formats
	VertexDescriptor VD;

	// Pipelines [Shader couples]
	Pipeline P;

	// Models, textures and Descriptors (values assigned to the uniforms)
	// Please note that Model objects depends on the corresponding vertex structure
	// Models
	
	// Other application parameters
	int currScene = 0;
	glm::vec3 CamPos = glm::vec3(0.0, 1.5, 7.0);
	float CamAlpha = 0.0f;
	float CamBeta = 0.0f;
	float Ar;

	// Here you set the main application parameters
	void setWindowParameters() {
		// window size, titile and initial background
		windowWidth = 800;
		windowHeight = 600;
		windowTitle = "Computer graphics";
    	windowResizable = GLFW_TRUE;
		initialBackgroundColor = {0.0f, 0.005f, 0.01f, 1.0f};
		
		// Descriptor pool sizes
		uniformBlocksInPool = 15 * 2 + 2;
		texturesInPool = 15 + 1 + 1;
		setsInPool = 15 + 1 + 1;

		Ar = 4.0f / 3.0f;
	}
	
	// What to do when the window changes size
	void onWindowResize(int w, int h) {
		std::cout << "Window resized to: " << w << " x " << h << "\n";
		Ar = (float)w / (float)h;
	}
	
	// Here you load and setup all your Vulkan Models and Texutures.
	// Here you also create your Descriptor set layouts and load the shaders for the pipelines
	void localInit() {
		// Descriptor Layouts [what will be passed to the shaders]
		DSL.init(this, {
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS},
					{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT},
					{2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS}
				});

		// Vertex descriptors
		VD.init(this, {
				  {0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX}
				}, {
				  {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos),
				         sizeof(glm::vec3), POSITION},
				  {0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, UV),
				         sizeof(glm::vec2), UV},
				  {0, 2, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, norm),
				         sizeof(glm::vec3), NORMAL}
				});

		// Pipelines [Shader couples]
		P.init(this, &VD, "shaders/PhongVert.spv", "shaders/PhongFrag.spv", {&DSL});
		P.setAdvancedFeatures(VK_COMPARE_OP_LESS_OR_EQUAL, VK_POLYGON_MODE_FILL,
 								    VK_CULL_MODE_NONE, false);

		Tpre[0] = glm::mat4(1.0f);
		Tpre[1] = glm::mat4(1.0f);
		Tpre[2] = glm::mat4(1, -0, 0, -0, -0, 1, -0, 0, 0, -0, 1, -0, -0, -3, 2, 1);
		Tpre[3] = glm::mat4(1, -0, 0, -0, -0, 0.866025f, -0.5f, 0, 0, 0.5f, 0.866025f, -0, -0, 0, -0, 1);
		Tpre[4] = glm::mat4(1, 0, -0, 0, 0, -1, 0, -0, -0, 0, 1, 0, 0, -0, 0, 1);
		Tpre[5] = glm::mat4(1, -0, 0, -0, -0.4f, 1, -0, 0, 0, -0, 1, -0, -0, 0, -0, 1);
		Tpre[6] = glm::mat4(1, -0, 0, -0, -0, 1.33333f, -0, 0, 0, -0, 0.666667f, -0, -0, 0, -0, 1);
		Tpre[7] = glm::mat4(0.4f, -0, 0, -0, -0, 0.4f, -0, 0, 0, -0, 0.4f, -0, -0, 0, -0, 1);
		Tpre[8] = glm::mat4(0.333333f, -0, 0, -0, -0, 0.333333f, -0, 0, 0, -0, 0.333333f, -0, -0.666667f, 0, 1.33333f, 1);
		Tpre[9] = glm::mat4(1, -0, 0, -0, -0, 0.833333f, 0.166667f, 0, 0, 0.166667f, 0.833333f, -0, -0, 0.5f, -0.5f, 1);
		Tpre[10] = glm::mat4(0.941421f, -0.117157f, 0.316228f, 0.0f, -0.117157f, 0.765685f, 0.632456f, 0.0f, -0.316228f, -0.632456f, 0.707107f, 0.0f, -2.83153f, -1.66305f, 1.48886f, 1.0f);
		Tpre[11] = glm::mat4(0.707107f, 0.707107f, 0, -0, -0.707107f, 0.707107f, -0, 0, 0, -0, 1, -0, 0.171573f, -2.41421f, -0, 1);
		Tpre[12] = glm::mat4(0.662267, 0.72438, 0.191511, 0.0,0.0403398, 0.220756, -0.974495, 0.0,-0.748182, 0.653101, 0.116978, 0.0,-1.49636, 1.3062, -1.76604, 1.0);
		Tpre[13] = glm::mat4(1, -0, 0, -0, -0, 0.5f, -0, 0, 0, -0, 1, -0, 2, 1, -3, 1);
		Tpre[14] = glm::mat4(-0.25f, 0.146447f, 0.957107f, -0, 0.853553f, 0.5f, 0.146447f, 0, -0.457107f, 0.853553f, -0.25f, 0, 4.72487f, -3.35355f, 1.98223f, 1);

	}
	
	// Here you create your pipelines and Descriptor Sets!
	void pipelinesAndDescriptorSetsInit() {
		// This creates a new pipeline (with the current surface), using its shaders
		P.create();
	}

	// Here you destroy your pipelines and Descriptor Sets!
	// All the object classes defined in Starter.hpp have a method .cleanup() for this purpose
	void pipelinesAndDescriptorSetsCleanup() {
		// Cleanup pipelines
		P.cleanup();
	}

	// Here you destroy all the Models, Texture and Desc. Set Layouts you created!
	// All the object classes defined in Starter.hpp have a method .cleanup() for this purpose
	// You also have to destroy the pipelines: since they need to be rebuilt, they have two different
	// methods: .cleanup() recreates them, while .destroy() delete them completely
	void localCleanup() {
		
		
		// Cleanup descriptor set layouts
		DSL.cleanup();
		
		// Destroies the pipelines
		P.destroy();		
	}
	
	// Here it is the creation of the command buffer:
	// You send to the GPU all the objects you want to draw,
	// with their buffers and textures
	
	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {
		// binds the pipeline
		P.bind(commandBuffer);

	}

	// Here is where you update the uniforms.
	// Very likely this will be where you will be writing the logic of your application.
	void updateUniformBuffer(uint32_t currentImage) {
		static bool debounce = false;
		static int curDebounce = 0;

		float deltaT;
		glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
		bool fire = false;
		getSixAxis(deltaT, m, r, fire);
		
		const float ROT_SPEED = glm::radians(120.0f);
		const float MOVE_SPEED = 2.0f;
		
		CamAlpha = CamAlpha - ROT_SPEED * deltaT * r.y;
		CamBeta  = CamBeta  - ROT_SPEED * deltaT * r.x;
		CamBeta  =  CamBeta < glm::radians(-90.0f) ? glm::radians(-90.0f) :
				   (CamBeta > glm::radians( 90.0f) ? glm::radians( 90.0f) : CamBeta);

		glm::vec3 ux = glm::rotate(glm::mat4(1.0f), CamAlpha, glm::vec3(0,1,0)) * glm::vec4(1,0,0,1);
		glm::vec3 uz = glm::rotate(glm::mat4(1.0f), CamAlpha, glm::vec3(0,1,0)) * glm::vec4(0,0,-1,1);
		CamPos = CamPos + MOVE_SPEED * m.x * ux * deltaT;
		CamPos = CamPos + MOVE_SPEED * m.y * glm::vec3(0,1,0) * deltaT;
		CamPos = CamPos + MOVE_SPEED * m.z * uz * deltaT;
		

		if(glfwGetKey(window, GLFW_KEY_SPACE)) {
			if(!debounce) {
				debounce = true;
				curDebounce = GLFW_KEY_SPACE;
				currScene = (currScene+1) % 2;
				std::cout << "Scene : " << currScene << "\n";

				if(!screenshotSaved) {
					saveScreenshot("VulkanApp.png", currentImage);
				}

				RebuildPipeline();
			}
		} else {
			if((curDebounce == GLFW_KEY_SPACE) && debounce) {
				debounce = false;
				curDebounce = 0;
			}
		}

		// Standard procedure to quit when the ESC key is pressed
		if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		

		glm::mat4 M = glm::perspective(glm::radians(45.0f), Ar, 0.1f, 50.0f);
		M[1][1] *= -1;

		glm::mat4 Mv =  glm::rotate(glm::mat4(1.0), -CamBeta, glm::vec3(1,0,0)) *
						glm::rotate(glm::mat4(1.0), -CamAlpha, glm::vec3(0,1,0)) *
						glm::translate(glm::mat4(1.0), -CamPos);

		glm::mat4 ViewPrj =  M * Mv;
		UniformBufferObject ubo{};
		glm::mat4 baseTr = glm::mat4(1.0f);								
		// Here is where you actually update your uniforms

		// updates global uniforms
		GlobalUniformBufferObject gubo{};
		gubo.lightDir = glm::vec3(cos(glm::radians(135.0f)), sin(glm::radians(135.0f)), 0.0f);
		gubo.lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		gubo.eyePos = CamPos;

		glm::mat4 AxTr = glm::scale(glm::mat4(1.0f), glm::vec3(0.0f));
		for(int i = 0; i < 15; i++) {
//			ubo.mMat = baseTr * Tpre[i] * AsTr[i] * Tpost[i];
			ubo.mMat = baseTr * Tpre[i] * mm[i];
			ubo.mvpMat = ViewPrj * ubo.mMat;
			ubo.nMat = glm::inverse(glm::transpose(ubo.mMat));
			if(mhil[i]) {
				ubo.overColor = glm::vec4(1.0f, 0.2f, 0.2f, 0.3f);
				AxTr = Tpre[i] * mm[i];
			} else {
				ubo.overColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
			}
		}
		ubo.mMat = baseTr * AxTr * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f,1.0f,0.0f));
		ubo.mvpMat = ViewPrj * ubo.mMat;
		ubo.nMat = glm::inverse(glm::transpose(ubo.mMat));

	}
};

ApiVulkan::ApiVulkan() {
  VulkanApp app;
  app.run();
}