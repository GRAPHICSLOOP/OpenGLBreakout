#pragma once
#include "GameObject.h"
class BallObject : public GameObject
{
public:
	GLfloat radius; // 半径
	glm::vec2 velocity; // 速度
	GLboolean stuck;
public:

	BallObject();

	/**
	 * 初始化.
	 * 
	 * \param pos
	 * \param radius 半径
	 * \param color
	 * \param texture
	 */
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec4 color, Texture2D* texture);

	/**
	 * 初始化.
	 *
	 * \param pos
	 * \param radius 半径
	 * \param color
	 * \param texture
	 */
	void Init(glm::vec2 pos, GLfloat radius, glm::vec4 color, Texture2D* texture);

	/**
	 * 移动.
	 * 
	 * \param detalTime
	 * \param screeenWidth 
	 */
	void Move(GLfloat detalTime,GLfloat screeenWidth);
};

