#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include <string>


namespace Engine::Input {

    enum class InputAction {
        Jump,
        Shoot,
        Equip,
        Inventory,
        MoveForward,
        MoveBackward,
        MoveLeft,
        MoveRight,
        LeftShift,
        LeftMouseButton,
        
        // Add more actions as needed
    };

    class InputManager {
    public:
        InputManager(GLFWwindow* window);

        bool IsActionPressed(InputAction action);
        void UpdateInputStates();

    private:
        GLFWwindow* window;
        std::map<InputAction, std::vector<int>> keyMappings;
        std::map<InputAction, std::vector<int>> mouseButtonMappings;
        std::map<InputAction, bool> inputStates;

    };

}

#endif // !INPUT_CLASS_H
