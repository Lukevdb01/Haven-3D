#include "Camera.h"

namespace Engine::View {

	Camera::Camera(int WIDTH, int HEIGHT, glm::vec3 position)
	{
		Camera::WIDTH = WIDTH;
		Camera::HEIGHT = HEIGHT;
		Position = position;
	}

	void Camera::Matrix(Shader& shader, const char* uniform)
	{
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	}

	void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
	{
		// Initializes matrices since otherwise they will be the null matrix
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		// Makes camera look in the right direction from the right position
		view = glm::lookAt(Position, Position + Orientation, Up);
		// Adds perspective to the scene
		projection = glm::perspective(glm::radians(FOVdeg), (float)WIDTH / HEIGHT, nearPlane, farPlane);

		// Sets new camera matrix
		cameraMatrix = projection * view;
	}

	void Camera::HandleInput(GLFWwindow* window, InputManager* inp)
	{
		inp_m = inp;

		if (inp_m->IsActionPressed(InputAction::MoveForward)) {
			Position += speed * Orientation;
		}

		if (inp_m->IsActionPressed(InputAction::MoveLeft)) {
			Position += speed * -glm::normalize(glm::cross(Orientation, Up));
		}

		if (inp_m->IsActionPressed(InputAction::MoveBackward)) {
			Position += speed * -Orientation;
		}

		if (inp_m->IsActionPressed(InputAction::MoveRight)) {
			Position += speed * glm::normalize(glm::cross(Orientation, Up));
		}

		if (inp_m->IsActionPressed(InputAction::Jump)) {
			Position += speed * Up;
		}

		if (inp_m->IsActionPressed(InputAction::LeftShift)) {
			speed = 0.5f;
		}
		else {
			speed = 0.1f;
		}

		if (inp_m->IsActionPressed(InputAction::LeftMouseButton)) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			if (fClick) {
				glfwSetCursorPos(window, (WIDTH / 2), (HEIGHT / 2));
				fClick = false;
			}

			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotX = sensitivity * (float)(mouseY - (HEIGHT / 2)) / HEIGHT;
			float rotY = sensitivity * (float)(mouseX - (WIDTH / 2)) / WIDTH;

			glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));
			if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
				Orientation = newOrientation;
			}

			Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
			glfwSetCursorPos(window, (WIDTH / 2), (HEIGHT / 2));
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			fClick = false;
		}
	}
}
