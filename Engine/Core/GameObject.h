#pragma once

#include <glm/glm.hpp>
#include "Texture2D.h"
#include "../Render/SpriteRender.h"
#include "ResourceManager.h"

class GameObject
{
public:
	GLboolean isSolid; // 可被销毁的物体
	GLboolean destroyed;// 是否被销毁了
	glm::vec2 pos;
	glm::vec2 size;
	glm::vec4 color;
	Texture2D* sprite;

public:
	GameObject();

	/**
	 * 初始化.
	 * 
	 * \param pos
	 * \param size
	 * \param color
	 * \param texture
	 */
	GameObject(glm::vec2 pos, glm::vec2 size, glm::vec4 color, Texture2D* texture);

	/**
	 * 初始化.
	 *
	 * \param pos
	 * \param size
	 * \param color
	 * \param texture
	 */
	void Init(glm::vec2 pos, glm::vec2 size, glm::vec4 color, Texture2D* texture);

	/**
	 * 调用渲染对象渲染该对象.
	 * 
	 * \param render 渲染器
	 */
	void DrawCall(SpriteRender& render);
};

