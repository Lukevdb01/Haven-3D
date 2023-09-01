#include "Application.h"
#include "shaders/Shader.h"
#include "buffers/VBO.h"
#include "buffers/VAO.h"
#include "buffers/EBO.h"

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
			// positions         // colors
			0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // top right (red)
			0.5f, -0.5f, 0.0f,  1.0f, 0.5f, 0.0f,   // bottom right (orange)
		   -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   // bottom left (yellow)
		   -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f    // top left (green)
		};

		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		// Create a GLFW window with the required parameters
		window = glfwCreateWindow(WIDTH, HEIGHT, "Haven engine - client", nullptr, nullptr);
		if (!window) {
			std::cout << "Failed to create a GLFW window\n" << std::endl;
		}
		glfwMakeContextCurrent(window);

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
		Shader shaderProgram("content/shaders/vertex.vert", "content/shaders/fragment.frag");
		// Create & Bind the vertex array ovject buffer
		VAO VAO1;
		VAO1.Bind();

		// Create & Set the Vertex buffer object buffer
		VBO VBO1(vertices, sizeof(vertices));
		// Create & Set the Element array object buffer
		EBO EBO1(indices, sizeof(indices));

		// Link the VBO to the VAO
		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));
		// Unbind all the buffers
		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();

		// Wireframe
		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

		// Main game-loop
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

			/* Swap front and back buffers */
			glClear(GL_COLOR_BUFFER_BIT);
			// Activate our shader program
			shaderProgram.Activate();

			// Update the uniform color
			float timeValue = glfwGetTime();
			float greenValue = sin(timeValue) / 2.0f + 0.5f;
			int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");
			glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

			// Bind the VAO buffer
			VAO1.Bind();
			// Draws the triangles to the screen
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			// Swap the buffers of the GLFW window
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
}
