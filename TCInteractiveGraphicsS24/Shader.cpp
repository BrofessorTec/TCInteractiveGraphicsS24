#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "TextFile.h"
#include "GraphicsObject.h"

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
	this->vertexSource = vertexSource;
	this->fragmentSource = fragmentSource;
	Init();
	CreateShaderProgram();
}

Shader::Shader()
{
	SetDefaultSource();
	Init();
	CreateShaderProgram();
}

void Shader::AddUniform(const std::string& uniformName)
{
	if (this->uniformMap.contains(uniformName))
	{
		return;
	}

	this->uniformMap[uniformName] = glGetUniformLocation(shaderProgram, uniformName.c_str());
}

void Shader::SendMat4Uniform(const std::string& uniformName, const glm::mat4& mat)
{
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(uniformMap[uniformName], 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetDefaultSource()
{
	// default source code here
	vertexSource =
		"#version 430\n"
		"layout(location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(position, 1.0);\n"
		"}\n";

	fragmentSource =
		"#version 430\n"
		"layout(location = 4) uniform vec4 uColor;\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		" color = uColor;\n"
		"}\n";

}

void Shader::Init()
{
	shaderProgram = 0;
}

unsigned int Shader::CompileShaderSource(int type, const std::string& shaderSource)
{
		unsigned shaderId = glCreateShader(type);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const char* source = (const char*)shaderSource.c_str();
		glShaderSource(shaderId, 1, &source, 0);

		glCompileShader(shaderId);

		int isCompiled = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			int maxLength = 0;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(shaderId);

			//Log(logger, infoLog);
			//result.isSuccess = false;
			//result.message = logger.str();
			Log(infoLog);
			return -1;
		}
		//result.isSuccess = true;
		//result.message = "Success!";
		Log("Success!");
		return shaderId;
}

void Shader::CreateShaderProgram()
{
	//Result result;

	unsigned int vertexShader =
		CompileShaderSource(GL_VERTEX_SHADER, vertexSource);

	//if (result.isSuccess == false) return result;
	if (vertexShader == -1) return;

	unsigned int fragmentShader =
		CompileShaderSource(GL_FRAGMENT_SHADER, fragmentSource);

	if (fragmentShader == -1) return;

	// Time to link the shaders together into a program.

	//unsigned int& program = shaderProgram;

	shaderProgram = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link our program
	glLinkProgram(shaderProgram);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	int isLinked = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(shaderProgram);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		Log(infoLog);
		//result.isSuccess = false;
		//result.message = logger.str();
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	//result.isSuccess = true;
	Log("Successfully created the shader!");
	return;
}

void Shader::SendIntUniform(const std::string& uniformName, int value)
{
	glUniform1i(uniformMap[uniformName], value); 
}

void Shader::SendVec3Uniform(const std::string& uniformName, const glm::vec3& vec)
{
	glUniform3fv(uniformMap[uniformName], 1, glm::value_ptr(vec));
	// is this right?
}

void Shader::SendFloatUniform(const std::string& uniformName, float value)
{
	glUniform1f(uniformMap[uniformName], value);
	// is this right?
}
