#include "Application.h"

namespace Engine {
	void Application::Run()
	{
		OnCreate();

		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
		glEnable(GL_DEPTH_TEST);

		// Main game-loop
		while (!glfwWindowShouldClose(w_win))
		{
			/* Render here */
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			/* Swap front and back buffers */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			OnUpdate();

		}
	}
}
