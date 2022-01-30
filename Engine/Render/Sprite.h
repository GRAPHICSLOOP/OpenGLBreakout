#pragma once
#include <glad/glad.h>

#include "../Core/ShaderManager.h"
#include "../Core/Texture2D.h"
class Sprite
{
private:
	GLuint quadVAO;

public:
	Sprite();
	~Sprite();
	/** 
	 * 绘制.
	 * 
	 * \param shader
	 * \param texture
	 * \param rotate 角度值
	 * \param pos 
	 * \param size 
	 * \param color 
	 */
	void Draw(ShaderManager* shader, Texture2D* texture, GLfloat rotate, glm::vec2 pos, glm::vec2 size, glm::vec4 color);
private:
	void InitRenderData();
};

