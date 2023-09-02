#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "input/input_manager.h"
#include "shaders/Shader.h"
#include "../Core.h"

using namespace Engine::Input;
using namespace Engine::Shaders;

namespace Engine::View {
    class ENGINE_API Camera {
    public:
        glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

        bool fClick = true;
        int WIDTH, HEIGHT;
        float speed = 0.5f, sensitivity = 100.0f;

        Camera(int WIDTH, int HEIGHT, glm::vec3 position);
        void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
        void HandleInput(GLFWwindow* window, InputManager* inp);
        InputManager* inp_m = nullptr;
    private:
    };
}

#endif // !CAMERA_CLASS_H
