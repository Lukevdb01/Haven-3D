#include "input_manager.h"

namespace Engine::Input {

    InputManager::InputManager(GLFWwindow* window) : window(window) {
        // Initialize mappings in the constructor
        keyMappings[InputAction::Jump] = { GLFW_KEY_SPACE };
        mouseButtonMappings[InputAction::Shoot] = { GLFW_MOUSE_BUTTON_LEFT };
        mouseButtonMappings[InputAction::Inventory] = { GLFW_KEY_I };
        mouseButtonMappings[InputAction::Equip] = { GLFW_KEY_E };
        keyMappings[InputAction::MoveForward] = { GLFW_KEY_W };
        keyMappings[InputAction::MoveLeft] = { GLFW_KEY_A };
        keyMappings[InputAction::MoveBackward] = { GLFW_KEY_S };
        keyMappings[InputAction::MoveRight] = { GLFW_KEY_D };
        // Add more mappings as needed
    }

    bool InputManager::IsActionPressed(InputAction action) {
        return inputStates[action];
    }

    void InputManager::UpdateInputStates() {
        for (auto& entry : inputStates) {
            bool isPressed = false;

            for (const auto& key : keyMappings[entry.first]) {
                if (glfwGetKey(window, key) == GLFW_PRESS) {
                    isPressed = true;
                    break;
                }
            }

            for (const auto& button : mouseButtonMappings[entry.first]) {
                if (glfwGetMouseButton(window, button) == GLFW_PRESS) {
                    isPressed = true;
                    break;
                }
            }

            entry.second = isPressed;
        }
    }

}
