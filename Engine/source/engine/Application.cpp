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
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};

		// Indices for vertices order
		unsigned int indices[] =
		{
			0, 1, 2,
			0, 2, 3,
			0, 1, 4,
			1, 2, 4,
			2, 3, 4,
			3, 0, 4
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
		Shader lightingShader("content/shaders/light_vertex.vs", "content/shaders/light_fragment.frag");
		Shader lightCubeShader("content/shaders/color_vertex.vs", "content/shaders/color_fragment.frag");
		// Create & Bind the vertex array ovject buffer
		VAO CubeVAO;
		CubeVAO.Bind();

		VBO RenderVBO(vertices, sizeof(vertices));
		CubeVAO.LinkAttrib(RenderVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		CubeVAO.LinkAttrib(RenderVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		CubeVAO.Unbind();


		VAO lightCubeVAO;
		lightCubeVAO.Bind();
		lightCubeVAO.LinkAttrib(RenderVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		lightCubeVAO.Unbind();

		RenderVBO.Unbind();

		// Wireframe
		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

		glEnable(GL_DEPTH_TEST);
		Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

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

			lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
			lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
			lightingShader.setVec3("lightPos", lightPos);

			// Handles camera inputs
			camera.HandleInput(window, inp_m);
			// Updates and exports the camera matrix to the Vertex Shader
			camera.Matrix(lightingShader, "camera_matrix");
			glm::mat4 model = glm::mat4(1.0f);
			lightingShader.setMat4("model", model);

			// Bind the VAO buffer
			CubeVAO.Bind();
			// Draws the triangles to the screen			
			glDrawArrays(GL_TRIANGLES, 0, 36);
			
			lightCubeShader.Activate();
			camera.Matrix(lightCubeShader, "camera_matrix");
			model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
			lightCubeShader.setMat4("model", model);

			lightCubeVAO.Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);

			// Swap the buffers of the GLFW window
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
			inp_m->UpdateInputStates();
			OnUpdate();
		}
	}
}
