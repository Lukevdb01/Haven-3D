#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

namespace Engine::Shaders {
	class Shader
	{
	public:
		unsigned int ID;
		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void Delete();

	private:
		std::string get_file_contents(const char* filename);
	};
}

#endif // !SHADER_CLASS_H

