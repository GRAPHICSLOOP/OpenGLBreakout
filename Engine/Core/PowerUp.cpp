#include "PowerUp.h"

PowerUp::PowerUp()
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::Init(std::string type, glm::vec4 color, GLfloat duration, glm::vec2 position, Texture2D* texture)
{
	GameObject::Init(position, POWERUP_SIZE, color, texture);
	this->duration = duration;
	this->type = type;
	this->active = false;
}
