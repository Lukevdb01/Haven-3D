#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "input/input_manager.h"
#include "Core.h"

// std
#include <iostream>

using namespace Engine::Input;

namespace Engine {
    class ENGINE_API Application {
    public:
        Application();
        virtual ~Application(); // Destructor to clean up allocated resources

        virtual void OnCreate() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnDestroy() = 0;

        void Run();
        InputManager* inp_m = nullptr;
    private:
        GLFWwindow* window;
        int WIDTH = 800, HEIGHT = 800;

    };

    // To be defined in CLIENT
    Application* CreateApplication();
}