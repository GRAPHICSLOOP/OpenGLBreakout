#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../Render/SpriteRender.h"
#include "ResourceManager.h"
#include "GameLevel.h"
#include "BallObject.h"
#include "ParticleGenerator.h"
#include "../Render/PostProcessor.h"

struct Player
{
	void Init(glm::vec2 pos,Texture2D* texture)
	{
		velocity = 400.f;
		obj = new GameObject();
		obj->Init(pos, glm::vec2(100.f, 20.f), glm::vec4(1.f), texture);
	}

	~Player()
	{
		delete obj;
	}

	GLfloat velocity;
	GameObject* obj;
};

enum class Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

// 碰撞属性<是否碰撞，碰撞方向，陷入盒子的插值>
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

class Game
{
public:
	GLuint screenWidth, screenHeight;
	GLboolean key[1024];
	std::vector<GameLevel> levels; // 关卡集合
	GLuint level; // 当前关卡
	SpriteRender spriteRender; // 渲染器
	Player play; // 玩家
	BallObject ballObj; // 球
	ParticleGenerator particleGenerator; // 粒子生成器
	PostProcessor postProcessor;
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

	/**
	 * AABB碰撞检查.
	 * 
	 * \param one 第一个物体
	 * \param two 第二个物体
	 */
	Collision CheckCollision(GameObject* one, GameObject* two);

	/**
	 * 场景物体碰撞检测.
	 * 
	 */
	void DoCollisionCheck();

	/**
	 * 检查向量方向.
	 * 
	 * \param target
	 * \return 方向
	 */
	Direction CheckVectionDirection(glm::vec2 target);

	void ResetLevel();
	void ResetPlay();
};



