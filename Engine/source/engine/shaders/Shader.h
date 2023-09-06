#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include <glm/glm.hpp>

namespace Engine::Shaders {
	class Shader
	{
	public:
		unsigned int ID;
		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void setMat4(const std::string& name, const glm::mat4& mat) const;
		void Delete();

		void setVec3(const std::string& name, const glm::vec3& value) const;
		void setVec3(const std::string& name, float x, float y, float z) const;
		void setFloat(const std::string& name, float value) const;
		void setInt(const std::string& name, int value) const;
	private:
		std::string get_file_contents(const char* filename);
		void compileErrors(unsigned int shader, const char* type);
	};
}

#endif // !SHADER_CLASS_H

