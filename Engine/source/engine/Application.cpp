#include "Application.h"

#include "shaders/Shader.h"
#include "buffers/VBO.h"
#include "buffers/VAO.h"
#include "buffers/EBO.h"
#include <textures/Texture.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Engine::Textures;
using namespace Engine::Buffers;
using namespace Engine::Shaders;

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
		float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

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

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
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
		Shader shaderProgram("content/shaders/vertex.vs", "content/shaders/fragment.frag");
		// Create & Bind the vertex array ovject buffer
		VAO VAO1;
		VAO1.Bind();

		// Create & Set the Vertex buffer object buffer
		VBO VBO1(vertices, sizeof(vertices));
		// Create & Set the Element array object buffer
		EBO EBO1(indices, sizeof(indices));

		// Link the VBO to the VAO
		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		// Unbind all the buffers
		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();

		Texture tex("content/textures/among_us.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		tex.texUnit(shaderProgram, "texture1", 0);

		// Wireframe
		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
		glEnable(GL_DEPTH_TEST);
		// Main game-loop
		OnCreate();

		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

			/* Swap front and back buffers */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Bind the texture so that it appears in the rendering
			tex.Bind();
			shaderProgram.Activate();

			// create transformations
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);

			projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
			shaderProgram.setMat4("projection", projection);
			shaderProgram.setMat4("view", view);
			// Bind the VAO buffer
			VAO1.Bind();
			// Draws the triangles to the screen
			//glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
			for (unsigned int i = 0; i < 10; i++)
			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);

				float angle = 20.0f * i;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				shaderProgram.setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			// Swap the buffers of the GLFW window
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
			inp_m->UpdateInputStates();
			OnUpdate();
		}
	}
}
