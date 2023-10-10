#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "../shaders/Shader.h"

using namespace Engine::Shaders;

namespace Engine::Textures {
	class Texture {
	public:
		unsigned int ID;
		const char* type;
		GLuint unit;
		Texture(const char* image, const char* texType, GLuint slot);

		void texUnit(Shader& shader, const char* uniform, unsigned int unit);
		void Bind();
		void Unbind();
		void Delete();
	};
}

#endif // !TEXTURE_CLASS_H
