// std
#include <iostream>

#include "Core.h"

namespace Engine {
    class ENGINE_API Application {
    public:
        Application();
        virtual ~Application(); // Destructor to clean up allocated resources

        virtual void OnCreate() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnDestroy() = 0;

        void Run();
    private:
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}