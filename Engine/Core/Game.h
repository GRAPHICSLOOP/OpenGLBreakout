#pragma once
#include <GLFW/glfw3.h>

class Game
{
public:
	GLuint screenWidth, screenHeight;

public:

	Game(GLuint width,GLuint height);
	~Game();

	// 初始化
	// -----------------------------------------------
	void Init();

	// 游戏循环
	// -----------------------------------------------
	void ProcessInput(GLfloat detalTime); // 玩家输入

	void Update(GLfloat detalTime); // 逻辑循环

	// 渲染循环
	// -----------------------------------------------
	void Render(); // 渲染循环
};

