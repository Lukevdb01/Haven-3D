#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

namespace Engine::Buffers {
	class VAO {
	public:
		unsigned int ID;
		VAO();

		void LinkVBO(VBO& VBO, unsigned int layout);
		void Bind();
		void Unbind();
		void Delete();
	};
}

#endif // !VAO_CLASS_H
