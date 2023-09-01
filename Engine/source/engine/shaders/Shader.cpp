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
		compileErrors(vertexShader, "VERTEX");

		// Create fragment shader object and get its reference
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		// Attach fragment shader source to the vertex shader object
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		// Compile the fragment shader int machine code
		glCompileShader(fragmentShader);
		compileErrors(fragmentShader, "FRAGMENT");

		// Create shader program object and get its reference
		ID = glCreateProgram();
		// Attach the vertex and fragment shaders to the shader program
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		// Wrap-up/link all the shaders together into the shader program
		glLinkProgram(ID);
		compileErrors(ID, "PROGRAM");

		// Delete the now useless Vertex and Fragment Shader objects
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Shader::Activate()
	{
		glUseProgram(ID);
	}

	void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
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

	void Shader::compileErrors(unsigned int shader, const char* type)
	{
		int hasCompiled;
		char infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
			}
		}
	}
}