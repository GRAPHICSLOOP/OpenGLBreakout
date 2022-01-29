#include "ShaderManager.h"

ShaderManager::ShaderManager(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr)
{
	// 编译shader
	unsigned int vertexShader, fragmentShader, geometryShader;
	int success;
	char infoLog[512];

	vertexShader = CompileShader(vertexSource, GL_VERTEX_SHADER);
	fragmentShader = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);
	if (geometrySource != nullptr)
		geometryShader = CompileShader(geometrySource, GL_GEOMETRY_SHADER);

	// shader 程序
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	if (geometrySource != nullptr)
		glAttachShader(ID, geometryShader);
	glLinkProgram(ID);

	// 打印错误
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// 删除shader，它们以及链接到程序中，因此不在需要
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometrySource != nullptr)
		glDeleteShader(geometryShader);
}

ShaderManager::~ShaderManager()
{
	glDeleteShader(ID);
}

void ShaderManager::use()
{
	glUseProgram(ID);
}

void ShaderManager::SetBool(const char* name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void ShaderManager::SetInt(const char* name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void ShaderManager::SetFloat(const char* name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void ShaderManager::SetVec3(const char* name, glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
}

void ShaderManager::SetVec4(const char* name, glm::vec4 value) const
{
	glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
}

void ShaderManager::SetVec2(const char* name, glm::vec2 value) const
{
	glUniform2fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
}

void ShaderManager::SetMatrix(const char* name, glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(mat));
}

GLuint ShaderManager::CompileShader(const char* shaderSource, GLenum type)
{
	// 编译shader
	unsigned int shader;
	int success;
	char infoLog[512];

	// shader
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::string shaderName = "VERTEX";
		switch (type)
		{
		case GL_VERTEX_SHADER :
			shaderName = "VERTEX";
			break;
		case GL_FRAGMENT_SHADER :
			shaderName = "FRAGMENT";
			break;
		case GL_GEOMETRY_SHADER :
			shaderName = "GEOMETRY";
			break;
		default:
			shaderName = "ERRORTYPE";
			break;
		}

		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shaderName << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

