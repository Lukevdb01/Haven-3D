#include "Source.h"

void Source::OnCreate()
{
	shaderProgram = new Shader("content/shaders/default.vs", "content/shaders/default.frag");
	model = new Model("content/assets/grindstone/scene.gltf");
	camera = new Camera(800, 800, glm::vec3(0.0f, 0.0f, 2.0f));
}

void Source::OnUpdate()
{
	camera->UpdateMatrix(45.0f, 0.1f, 100.0f);
	shaderProgram->Activate();

	camera->Matrix(*shaderProgram, "camMatrix");
	model->Draw(*shaderProgram, *camera);
}

void Source::OnDestroy()
{
}
