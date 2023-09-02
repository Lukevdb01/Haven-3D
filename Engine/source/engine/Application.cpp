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
		float vertices[] = {
			-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
			-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
			0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
			0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
			0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
		};

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
		Shader shaderProgram("content/shaders/vertex.vs", "content/shaders/fragment.frag");
		// Create & Bind the vertex array ovject buffer
		VAO VAO1;
		VAO1.Bind();

		// Create & Set the Vertex buffer object buffer
		VBO VBO1(vertices, sizeof(vertices));
		// Create & Set the Element array object buffer
		EBO EBO1(indices, sizeof(indices));

		// Link the VBO to the VAO
		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		// Unbind all the buffers
		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();

		Texture tex("content/textures/among_us.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		tex.texUnit(shaderProgram, "texture1", 0);

		// Wireframe
		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

		glEnable(GL_DEPTH_TEST);
		Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

		OnCreate();

		// Main game-loop
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

			/* Swap front and back buffers */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Bind the texture so that it appears in the rendering
			tex.Bind();
			shaderProgram.Activate();

			// Handles camera inputs
			camera.HandleInput(window, inp_m);
			// Updates and exports the camera matrix to the Vertex Shader
			camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

			// Bind the VAO buffer
			VAO1.Bind();
			// Draws the triangles to the screen
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

			// Swap the buffers of the GLFW window
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
			inp_m->UpdateInputStates();
			OnUpdate();
		}
	}
}
