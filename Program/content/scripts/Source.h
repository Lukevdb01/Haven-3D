#include <Engine.h>

class Source : public Engine::Application
{
public:
	// Inherited via Application
	void OnCreate() override;

	void OnUpdate() override;

	void OnDestroy() override;
};

Engine::Application* Engine::CreateApplication()
{
	return new Source();
}