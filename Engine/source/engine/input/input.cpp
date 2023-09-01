#include "input.h"

namespace Engine::Input {

    InputManager::InputManager(GLFWwindow* window) : window(window) {}

    void InputManager::AddMapping(const std::string& actionName, const std::vector<int>& keys, const std::vector<int>& mouseButtons) {
        keyMappings[actionName] = keys;
        mouseButtonMappings[actionName] = mouseButtons;
    }

    bool InputManager::IsActionPressed(const std::string& actionName) {
        return inputStates[actionName];
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