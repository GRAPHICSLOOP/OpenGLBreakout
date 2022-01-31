#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../Core/ShaderManager.h"
#include "../Core/Texture2D.h"

class SpriteRender
{
private:
	GLuint quadVAO;
public:
	ShaderManager* shader;

public:
	SpriteRender();
	~SpriteRender();
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
	void Draw(Texture2D* texture, GLfloat rotate, glm::vec2 pos, glm::vec2 size, glm::vec4 color);

	// 初始化
	void Init(ShaderManager* shader);
};

