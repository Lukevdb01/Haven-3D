#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

namespace Engine::Buffers {
	class EBO {
	public:
		unsigned int ID;

		EBO(unsigned int* indices, size_t size);

		void Bind();
		void Unbind();
		void Delete();
	};
}

#endif // !EBO_CLASS_H
