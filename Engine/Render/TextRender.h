#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include "../Core/ShaderManager.h"
#include "../Core/ResourceManager.h"
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character
{
	GLuint textureID; // 字形贴图
	glm::ivec2 size; // 字形尺寸
	glm::ivec2 bearing; // 水平偏移和垂直偏移（基准线上的）
	GLuint advance; // 到下一个字符的水平距离
};

class TextRender
{
private:
	GLuint VBO, VAO;

public:
	std::map<GLchar, Character> characters; // 缓冲的字符
	ShaderManager* shader;

	/**
	 * 初始化.
	 * 
	 * \param width 屏幕
	 * \param height 屏幕
	 */
	void Init(GLuint width, GLuint height);

	/**
	 * 加载字体.
	 * 
	 * \param fontFile
	 * \param fontSize
	 */
	void Load(const char* fontFile, GLuint fontSize);
	
	/**
	 * 渲染.
	 * 
	 * \param text 要渲染的文字
	 * \param x 屏幕上的位置
	 * \param y 屏幕上的位置
	 * \param scale
	 * \param color
	 */
	void Render(const std::string& text, GLfloat x, GLfloat y, GLfloat scale = 1.f, glm::vec4 color = glm::vec4(1.f));
};

