#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "BallObject.h"
#include "../Render/SpriteRender.h"
#include "Texture2D.h"

#define INIT_PARTICLE_SIZE 10

struct Particle
{
	glm::vec2 pos;
	glm::vec2 size;
	glm::vec4 color;
	GLfloat life; // 生命值
	glm::vec2 velocity; // 速度

	Particle()
	{
		pos = glm::vec2(0.f);
		size = glm::vec2(1.f);
		color = glm::vec4(1.f);
		life = 0.f;
		velocity = glm::vec2(0.f);
	}
};

class ParticleGenerator
{
private:
	GLuint amount; // 粒子最大数量
	Particle* particles; // 粒子
	GLuint lastDeadParticle;

public:
	Texture2D* texture;

public:
	ParticleGenerator();
	~ParticleGenerator();

	/**
	 * 初始化.
	 * 
	 * \param amount 粒子最大数量
	 * \param texutre 贴图
	 */
	void Init(GLuint amount, Texture2D* texture);

	/**
	 * 更新粒子.
	 * 
	 * \param detalTime 
	 * \param attachObj 附着的对象
	 */
	void Update(GLfloat detalTime, BallObject* attachObj);

	// 查找最后死亡的粒子
	GLuint FindLastDeadParticle();

	/**
	 * 重新生成粒子.
	 * 
	 * \param index 死亡的粒子
	 * \param attachObj 附着的对象
	 */
	void RespwanDeadParticle(GLuint index,BallObject* attachObj);

	/**
	 * 绘制粒子.
	 * 
	 * \param Render 渲染器
	 */
	void DrawCall(SpriteRender* Render);
};

