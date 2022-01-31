#pragma once

#include <glad/glad.h>

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CommonTool.h"

class ShaderManager
{

public:
	// shader ID
	GLuint ID;

	// 构造shader
	ShaderManager(const char* vertexSource, const char* fragmentSource, const char* geometrySource);
	~ShaderManager();

	// 激活shader
	void use();

	// uniform工具函数
	// -------------------------------------------

	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetVec2(const char* name, glm::vec2 value) const;
	void SetVec3(const char* name, glm::vec3 value) const;
	void SetVec4(const char* name, glm::vec4 value) const;
	void SetMatrix(const char* name, glm::mat4& mat);

private:

	/**
	 * 编译shader.
	 * 
	 * \param shaderSource shader代码
	 * \param type shader类型
	 * \return 
	 */
	GLuint CompileShader(const char* shaderSource, GLenum type);
};
