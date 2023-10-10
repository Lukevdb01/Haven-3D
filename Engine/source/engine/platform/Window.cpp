#include "window.h"

namespace Engine::Platform {

	Window::Window(int width, int height, const char* title)
	{
		// Initialize GLFW
		glfwInit();
		// Tell GLFW what version we use of OpenGL
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		// Tell GLFW that we want to use the OpenGL core profile
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		win_p.height = height;
		win_p.width = width;
		win_p.title = title;
	}

	void Window::CreateWindow()
	{
		// Create a GLFW window with the required parameters
		win = glfwCreateWindow(win_p.width, win_p.height, "Haven engine - client", nullptr, nullptr);
		if (!win) {
			std::cout << "Failed to create a GLFW window\n" << std::endl;
		}
		glfwMakeContextCurrent(win);

		// Load GLAD (Modern OpenGL)
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD\n" << std::endl;
		}

		// Tell the user the num of vertexs supported by the hardware
		int nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

		glViewport(0, 0, 800, 800);
	}

	void Window::Update()
	{
		// Swap the buffers of the GLFW window
		glfwSwapBuffers(win);
		/* Poll for and process events */
		glfwPollEvents();
	}

	void Window::DestroyWindow()
	{
		// Get rid of any references that we dont need anymore
		glfwDestroyWindow(win);
		glfwTerminate();
	}

	Window::~Window()
	{
		DestroyWindow();
	}

}