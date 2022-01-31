#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../Render/SpriteRender.h"
#include "ResourceManager.h"
#include "GameLevel.h"

struct Player
{
	void Init(glm::vec2 pos,Texture2D* texture)
	{
		velocity = 400.f;
		obj = new GameObject(pos, glm::vec2(100.f, 20.f),glm::vec4(1.f), texture);
	}

	~Player()
	{
		delete obj;
	}

	GLfloat velocity;
	GameObject* obj;
};

class Game
{
public:
	GLuint screenWidth, screenHeight;
	GLboolean key[1024];
	std::vector<GameLevel> levels;
	GLuint level;
	SpriteRender spriteRender;
	Player play;

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

