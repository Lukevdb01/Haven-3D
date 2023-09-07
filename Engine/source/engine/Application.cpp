#include "Application.h"

#include "shaders/Shader.h"
#include "buffers/VBO.h"
#include "buffers/VAO.h"
#include "buffers/EBO.h"
#include <textures/Texture.h>
#include "camera/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Engine::Textures;
using namespace Engine::Buffers;
using namespace Engine::Shaders;
using namespace Engine::View;

namespace Engine {
	Application::Application()
	{
		// Initialize GLFW
		glfwInit();
		// Tell GLFW what version we use of OpenGL
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		// Tell GLFW that we want to use the OpenGL core profile
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	Application::~Application()
	{
		// Get rid of any references that we dont need anymore
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Application::Run()
	{
		glm::vec3 lightPos(0.0f, 1.0f, 1.0f);
		float vertices[] = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
		};
		// positions all containers
		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};
		// positions of the point lights
		glm::vec3 pointLightPositions[] = {
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
		};

		// Create a GLFW window with the required parameters
		window = glfwCreateWindow(WIDTH, HEIGHT, "Haven engine - client", nullptr, nullptr);
		if (!window) {
			std::cout << "Failed to create a GLFW window\n" << std::endl;
		}
		glfwMakeContextCurrent(window);

		inp_m = new InputManager(window);

		// Load GLAD (Modern OpenGL)
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD\n" << std::endl;
		}

		// Tell the user the num of vertexs supported by the hardware
		int nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

		// Set the glViewport with the height & width
		glViewport(0, 0, WIDTH, HEIGHT);

		// Tell our shader program where the shader files are located
		Shader lightingShader("content/shaders/material_vertex.vs", "content/shaders/material_fragment.frag");
		Shader lightCubeShader("content/shaders/color_vertex.vs", "content/shaders/color_fragment.frag");
		// Create & Bind the vertex array ovject buffer
		VAO CubeVAO;
		CubeVAO.Bind();

		VBO RenderVBO(vertices, sizeof(vertices));
		CubeVAO.LinkAttrib(RenderVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		CubeVAO.LinkAttrib(RenderVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		CubeVAO.LinkAttrib(RenderVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		CubeVAO.Unbind();


		VAO lightCubeVAO;
		lightCubeVAO.Bind();
		lightCubeVAO.LinkAttrib(RenderVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		lightCubeVAO.Unbind();

		RenderVBO.Unbind();

		Texture tex("content/textures/container.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
		Texture tex_spec("content/textures/container_specular.png", GL_TEXTURE_2D, 1, GL_RGBA, GL_UNSIGNED_BYTE);

		lightingShader.Activate();

		lightingShader.setInt("materials.diffuse", 0);
		lightingShader.setInt("materials.specular", 1);
		// Wireframe
		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
		glEnable(GL_DEPTH_TEST);
		Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 3.0f));

		OnCreate();

		// Main game-loop
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			/* Swap front and back buffers */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

			lightingShader.Activate();
			//lightingShader.setVec3("light.position", lightPos);
			/*lightingShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);*/
			lightingShader.setVec3("viewPos", camera.Position);
			lightingShader.setFloat("material.shininess", 64.0f);

			lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
			lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
			lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
			lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
			// point light 1
			lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
			lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
			lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
			lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
			lightingShader.setFloat("pointLights[0].constant", 1.0f);
			lightingShader.setFloat("pointLights[0].linear", 0.09f);
			lightingShader.setFloat("pointLights[0].quadratic", 0.032f);
			// point light 2
			lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
			lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
			lightingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
			lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
			lightingShader.setFloat("pointLights[1].constant", 1.0f);
			lightingShader.setFloat("pointLights[1].linear", 0.09f);
			lightingShader.setFloat("pointLights[1].quadratic", 0.032f);
			// point light 3
			lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
			lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
			lightingShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
			lightingShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
			lightingShader.setFloat("pointLights[2].constant", 1.0f);
			lightingShader.setFloat("pointLights[2].linear", 0.09f);
			lightingShader.setFloat("pointLights[2].quadratic", 0.032f);
			// point light 4
			lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
			lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
			lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
			lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
			lightingShader.setFloat("pointLights[3].constant", 1.0f);
			lightingShader.setFloat("pointLights[3].linear", 0.09f);
			lightingShader.setFloat("pointLights[3].quadratic", 0.032f);

			// Handles camera inputs
			camera.HandleInput(window, inp_m);
			// Updates and exports the camera matrix to the Vertex Shader
			camera.Matrix(lightingShader, "camera_matrix");
			glm::mat4 model = glm::mat4(1.0f);
			lightingShader.setMat4("model", model);
			tex_spec.Bind();
			tex.Bind();
			// Bind the VAO buffer
			CubeVAO.Bind();
			for (unsigned int i = 0; i < 10; i++)
			{
				// calculate the model matrix for each object and pass it to shader before drawing
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				float angle = 20.0f * i;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				lightingShader.setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			
			lightCubeShader.Activate();
			camera.Matrix(lightCubeShader, "camera_matrix");
		
			lightCubeVAO.Bind();
			for (unsigned int i = 0; i < 4; i++)
			{
				model = glm::mat4(1.0f);
				model = glm::translate(model, pointLightPositions[i]);
				model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
				lightCubeShader.setMat4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			//glDrawArrays(GL_TRIANGLES, 0, 36);

			// Swap the buffers of the GLFW window
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
			inp_m->UpdateInputStates();
			OnUpdate();
		}
	}
}
