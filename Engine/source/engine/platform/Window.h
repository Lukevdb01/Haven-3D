#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Core.h"

namespace Engine::Platform {
	struct WindowProps {
		int width, height;
		const char* title;
	};

	class ENGINE_API Window {
	public:
		Window(int width, int height, const char* title);
		~Window();

		void CreateWindow();
		void Update();
		void DestroyWindow();

		GLFWwindow* win;
	private:
		WindowProps win_p;
	};
}

#endif // !WINDOW_CLASS_H
