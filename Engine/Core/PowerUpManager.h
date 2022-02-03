#pragma once
#include <vector>
#include "PowerUp.h"
#include "BallObject.h"
#include "../Render/PostProcessor.h"

class PowerUpManager
{
public:
	std::vector<PowerUp> powerUps;

public:
	/**
	 * 生成道具.
	 * 
	 * \param block 
	 */
	void SpawnPowerUps(GameObject& block);

	/**
	 * 更新逻辑.
	 * 
	 * \param dt
	 */
	void Update(GLfloat dt, BallObject* ball, GameObject* play, PostProcessor* post);

	/**
	 * 激活道具.
	 * 
	 * \param powerUp 要激活的道具
	 * \param ball
	 * \param play
	 * \param post
	 */
	void ActivatePowerUp(PowerUp* powerUp, BallObject* ball,GameObject* play, PostProcessor* post);

	/**
	 * 渲染.
	 * 
	 * \param render
	 */
	void Render(SpriteRender& render);
};

