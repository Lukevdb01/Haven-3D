#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

namespace Engine::Buffers {
	class EBO {
	public:
		unsigned int ID;

		EBO(std::vector<GLuint>& indices);

		void Bind();
		void Unbind();
		void Delete();
	};
}

#endif // !EBO_CLASS_H
