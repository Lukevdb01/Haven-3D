#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include <string>

#include "../Core.h"

namespace Engine::Input {

    class ENGINE_API InputManager {
    public:
        InputManager(GLFWwindow* window);

        void AddMapping(const std::string& actionName, const std::vector<int>& keys, const std::vector<int>& mouseButtons);
        bool IsActionPressed(const std::string& actionName);
        void UpdateInputStates();

    private:
        GLFWwindow* window;
        std::map<std::string, std::vector<int>> keyMappings;
        std::map<std::string, std::vector<int>> mouseButtonMappings;
        std::map<std::string, bool> inputStates;

    };

}

#endif // !INPUT_CLASS_H
