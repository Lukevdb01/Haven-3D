#include <Engine.h>

using namespace Engine::Shaders;
using namespace Engine::Model_Loader;
using namespace Engine::View;

class Source : public Engine::Application
{
public:

	// Inherited via Application
	void OnCreate() override;

	void OnUpdate() override;

	void OnDestroy() override;
private:
	Shader* shaderProgram = nullptr;
	Camera* camera = nullptr;
	Model* model = nullptr;
};

Engine::Application* Engine::CreateApplication()
{
	return new Source();
}