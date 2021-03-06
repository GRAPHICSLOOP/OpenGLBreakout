#include "BallObject.h"


BallObject::BallObject()
{
}


void BallObject::Init(glm::vec2 pos, GLfloat radius, glm::vec4 color, Texture2D* texture)
{
	GameObject::Init(pos, glm::vec2(radius * 2.f), color, texture);
	this->radius = radius;
	this->velocity = INIT_BALL_VELOCITY;
	stuck = true;
	passThrough = false;
	sticky = false;
}

void BallObject::Move(GLfloat detalTime, GLfloat screeenWidth)
{
	if (stuck)
		return;

	pos += detalTime * velocity;

	// 右边界
	if (pos.x + size.x >= screeenWidth)
		velocity.x = -velocity.x;

	// 左边界
	if (pos.x < 0.f)
		velocity.x = -velocity.x;

	// 上边界
	if (pos.y < 0.f)
		velocity.y = -velocity.y;

}
