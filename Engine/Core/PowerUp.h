#pragma once
#include "GameObject.h"

const glm::vec2 POWERUP_SIZE(60, 20);
const glm::vec2 POWERUP_VELOCITY(0.0f, 150.0f);

class PowerUp : public GameObject
{
public:
	std::string type;
	GLfloat duration;
	GLboolean active; // 激活
public:
	PowerUp();
	~PowerUp();

	void Init(std::string type, glm::vec4 color, GLfloat duration, glm::vec2 position, Texture2D* texture);
};

