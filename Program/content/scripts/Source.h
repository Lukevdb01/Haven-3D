#include <Engine.h>

using namespace Engine::Shaders;
using namespace Engine::Model_Loader;
using namespace Engine::View;

class Source : public Engine::Application
{
public:
	int WIDTH = 800, HEIGHT = 800;

public:
	Source() : window(WIDTH, HEIGHT, "")
	{
		window.CreateWindow();
		w_win = window.win;
		
		camera = new Camera(800, 800, glm::vec3(0.0f, 0.0f, 2.0f));
		inp_m = new InputManager(w_win);
	}

public:
	// Inherited via Application
	void OnCreate() override;

	void OnUpdate() override;

	void OnDestroy() override;

private:
	Shader* shaderProgram = nullptr;
	Camera* camera = nullptr;
	Model* model = nullptr;
	Engine::Platform::Window window;
	Engine::Input::InputManager* inp_m;
};

Engine::Application* Engine::CreateApplication()
{
	return new Source();
}