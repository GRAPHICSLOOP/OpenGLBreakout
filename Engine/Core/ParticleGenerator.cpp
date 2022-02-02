#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator()
{
	lastDeadParticle = 0;
}

ParticleGenerator::~ParticleGenerator()
{
	delete particles;
}

void ParticleGenerator::Init(GLuint amount,Texture2D* texture)
{
	this->amount = amount;
	this->texture = texture;
	particles = new Particle[amount];
}

void ParticleGenerator::Update(GLfloat detalTime, BallObject* attachObj)
{
	// 更新最后死亡的粒子
	for (int i = 0; i < 2; i++)
	{
		GLuint Dead = FindLastDeadParticle();
		RespwanDeadParticle(Dead,attachObj);
	}

	// 更新存活的粒子
	for (GLuint i = 0; i < amount; i++)
	{
		particles[i].life -= detalTime;
		if (particles[i].life > 0.f)
		{
			particles[i].pos += particles[i].velocity * detalTime;
			particles[i].color.a -= detalTime * 2.f;
		}
	}
}

GLuint ParticleGenerator::FindLastDeadParticle()
{
	// 先后查找，因为死亡的总是在下一个
	for (GLuint i = lastDeadParticle; i < amount; i++)
	{
		if (particles[i].life <= 0.f)
		{
			lastDeadParticle = i;
			return i;
		}
	}

	// 向前查找，因为死亡可能是最后一个了
	for (GLuint i = 0; i < lastDeadParticle; i++)
	{
		if (particles[i].life <= 0.f)
		{
			lastDeadParticle = i;
			return i;
		}
	}
	lastDeadParticle = 0;
	return 0;
}

void ParticleGenerator::RespwanDeadParticle(GLuint index, BallObject* attachObj)
{
	Particle& particle = particles[index];
	GLfloat random = ((rand() % 100) - 50) / 10.0f;
	GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
	particle.pos = attachObj->pos + random;
	particle.color = glm::vec4(rColor, rColor, rColor, 1.0f);
	particle.life = 1.0f;
	particle.velocity = attachObj->velocity * 0.1f;
	particle.size = glm::vec2(10.f);
}

void ParticleGenerator::DrawCall(SpriteRender* Render)
{
	for (GLuint i = 0; i < amount; i++)
	{
		Render->Draw(texture, 0.f, particles[i].pos, particles[i].size, particles[i].color);
	}
}




