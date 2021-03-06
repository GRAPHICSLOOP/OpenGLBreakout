#pragma once
#include "GameObject.h"

#define INIT_BALL_VELOCITY glm::vec2(100.f, -350.f)

class BallObject : public GameObject
{

public:
	GLfloat radius; // 半径
	glm::vec2 velocity; // 速度
	GLboolean stuck;
	GLboolean passThrough; // 不受碰撞影响
	GLboolean sticky; // 不受碰撞影响
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
	void Init(glm::vec2 pos, GLfloat radius, glm::vec4 color, Texture2D* texture);

	/**
	 * 移动.
	 * 
	 * \param detalTime
	 * \param screeenWidth 
	 */
	void Move(GLfloat detalTime,GLfloat screeenWidth);
};

