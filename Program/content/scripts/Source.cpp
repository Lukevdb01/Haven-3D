#include "Source.h"

void Source::OnCreate()
{
	shaderProgram = new Shader("content/shaders/default.vs", "content/shaders/default.frag");
	model = new Model("content/assets/grindstone/scene.gltf");
}

void Source::OnUpdate()
{
	camera->UpdateMatrix(45.0f, 0.1f, 100.0f);
	shaderProgram->Activate();

	camera->HandleInput(w_win, inp_m);
	camera->Matrix(*shaderProgram, "camMatrix");
	model->Draw(*shaderProgram, *camera);

	inp_m->UpdateInputStates();
	window.Update();
}

void Source::OnDestroy()
{
	shaderProgram->Delete();
}
