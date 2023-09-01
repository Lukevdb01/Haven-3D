#include "VAO.h"

namespace Engine::Buffers {
	VAO::VAO()
	{
		glGenVertexArrays(1, &ID);
	}

	void VAO::LinkVBO(VBO& VBO, unsigned int layout)
	{
		VBO.Bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		VBO.Unbind();
	}

	void VAO::Bind()
	{
		glBindVertexArray(ID);
	}

	void VAO::Unbind()
	{
		glBindVertexArray(0);
	}

	void VAO::Delete()
	{
		glDeleteVertexArrays(1, &ID);
	}
}