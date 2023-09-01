#include "Application.h"
#include "shaders/Shader.h"
#include "buffers/VBO.h"
#include "buffers/VAO.h"

using namespace Engine::Buffers;
using namespace Engine::Shaders;

namespace Engine {
	Application::Application()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	Application::~Application()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Application::Run()
	{
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};

		window = glfwCreateWindow(WIDTH, HEIGHT, "Haven engine - client", nullptr, nullptr);
		if (!window) {
			std::cout << "Failed to create a GLFW window\n" << std::endl;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD\n" << std::endl;
		}
		glViewport(0, 0, WIDTH, HEIGHT);

		Shader shaderProgram("content/shaders/vertex.vert", "content/shaders/fragment.frag");
		VAO VAO1;
		VAO1.Bind();
		VBO VBO1(vertices, sizeof(vertices));
		VAO1.LinkVBO(VBO1, 0);
		VAO1.Unbind();
		VBO1.Unbind();

		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

			/* Swap front and back buffers */
			glClear(GL_COLOR_BUFFER_BIT);
			shaderProgram.Activate();
			VAO1.Bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
}
