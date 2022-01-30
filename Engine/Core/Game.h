#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../Render/Sprite.h"
#include "ResourceManager.h"


class Game
{
public:
	GLuint screenWidth, screenHeight;
	Sprite* spriteObj;

public:

	Game(GLuint width,GLuint height);
	~Game();

	/**
	 * 初始化.
	 * 
	 */
	void Init();

	/**
	 * 玩家输入.
	 * 
	 * \param deltaTime
	 */
	void ProcessInput(GLfloat deltaTime);

	/**
	 * 逻辑循环.
	 * 
	 * \param detalTime
	 */
	void Update(GLfloat detalTime);

	/**
	 * 渲染循环.
	 * 
	 */
	void Render();
};

