#include "Shader.h"

namespace Engine::Shaders {
	Shader::Shader(const char* vertexFile, const char* fragmentFile)
	{
		// Read vertexFile and fragmentFile and store the strings
		std::string vertexCode = get_file_contents(vertexFile);
		std::string fragmentCode = get_file_contents(fragmentFile);

		// Convert the shader source strings into character arrays
		const char* vertexSource = vertexCode.c_str();
		const char* fragmentSource = fragmentCode.c_str();

		// Create vertex shader object and get its reference
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		// Attach vertex shader source to the vertex shader object
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		// Compile the vertex shader int machine code
		glCompileShader(vertexShader);

		// Create fragment shader object and get its reference
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		// Attach fragment shader source to the vertex shader object
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		// Compile the fragment shader int machine code
		glCompileShader(fragmentShader);

		// Create shader program object and get its reference
		ID = glCreateProgram();
		// Attach the vertex and fragment shaders to the shader program
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		// Wrap-up/link all the shaders together into the shader program
		glLinkProgram(ID);

		// Delete the now useless Vertex and Fragment Shader objects
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Shader::Activate()
	{
		glUseProgram(ID);
	}

	void Shader::Delete()
	{
		glDeleteProgram(ID);
	}

	std::string Shader::get_file_contents(const char* filename)
	{
		std::ifstream in(filename, std::ios::binary);
		if (in) {
			std::string content;
			in.seekg(0, std::ios::end);
			content.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&content[0], content.size());
			in.close();
			return (content);
		}
		throw(errno);
	}
}