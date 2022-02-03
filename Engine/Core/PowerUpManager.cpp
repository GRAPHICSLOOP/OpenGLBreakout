#include "PowerUpManager.h"

GLboolean IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type)
{
    for (const PowerUp& powerUp : powerUps)
    {
        if (powerUp.active)
            if (powerUp.type == type)
                return GL_TRUE;
    }
    return GL_FALSE;
}

/**
 * 是否生成.
 * 
 * \param chance 几率
 * \return 
 */
GLboolean ShouldSpawn(GLuint chance)
{
    GLuint random = rand() % chance;
    return random == 0;
}

void PowerUpManager::SpawnPowerUps(GameObject& block)
{
    if (ShouldSpawn(75))
    {
        PowerUp powerUp;
        powerUp.Init("speed", glm::vec4(0.5f, 0.5f, 1.0f, 1.f), 0.0f, block.pos, ResourceManager::LoadTexture("PowerupSpeed", "./Resources/powerup_speed.png"));
        powerUps.push_back(powerUp);
    }

    if (ShouldSpawn(75))
    {
        PowerUp powerUp;
        powerUp.Init("sticky", glm::vec4(1.0f, 0.5f, 1.0f, 1.f), 20.0f, block.pos, ResourceManager::LoadTexture("PowerupSticky", "./Resources/powerup_sticky.png"));
        powerUps.push_back(powerUp);
    }

    if (ShouldSpawn(75))
    {
        PowerUp powerUp;
        powerUp.Init("pass-through", glm::vec4(0.5f, 1.0f, 0.5f, 1.f), 10.0f, block.pos, ResourceManager::LoadTexture("PowerupPassthrough", "./Resources/powerup_passthrough.png"));
        powerUps.push_back(powerUp);
    }

    if (ShouldSpawn(75))
    {
        PowerUp powerUp;
        powerUp.Init("pad-size-increase", glm::vec4(1.0f, 0.6f, 0.4f, 1.f), 0.0f, block.pos, ResourceManager::LoadTexture("PowerupIncrease", "./Resources/powerup_increase.png"));
        powerUps.push_back(powerUp);
    }

    if (ShouldSpawn(15))
    {
        PowerUp powerUp;
        powerUp.Init("confuse", glm::vec4(1.0f, 0.3f, 0.3f, 1.f), 3.0f, block.pos, ResourceManager::LoadTexture("PowerupConfuse", "./Resources/powerup_confuse.png"));
        powerUps.push_back(powerUp);
    }

    if (ShouldSpawn(15))
    {
        PowerUp powerUp;
        powerUp.Init("chaos", glm::vec4(1.0f, 0.3f, 0.3f, 1.f), 3.0f, block.pos, ResourceManager::LoadTexture("PowerupChaos", "./Resources/powerup_chaos.png"));
        powerUps.push_back(powerUp);
    }
}

void PowerUpManager::Update(GLfloat dt, BallObject* ball, GameObject* play, PostProcessor* post)
{
    for (PowerUp& it : powerUps)
    {
        if (it.active)
        {
            it.duration -= dt;
            if (it.duration < 0.f)
            {
                it.active = false;

                if (it.type == "sticky")
                {
                    if (IsOtherPowerUpActive(powerUps, "sticky"))
                        break;
                    ball->sticky = false;
                    play->color = glm::vec4(1.f);
                    break;
                }

                if (it.type == "pass-through")
                {
                    if (IsOtherPowerUpActive(powerUps, "pass-through"))
                        break;
                    ball->passThrough = false;
                    ball->color = glm::vec4(1.f);
                    break;
                }

                if (it.type == "confuse")
                {
                    if (IsOtherPowerUpActive(powerUps, "confuse"))
                        break;
                    post->confuse = false;
                    break;
                }

                if (it.type == "chaos")
                {
                    if (IsOtherPowerUpActive(powerUps, "chaos"))
                        break;
                    post->chaos = false;
                    break;
                }
            }
        }
        else
        {
            it.pos += POWERUP_VELOCITY * dt;
        }
    }

    // 清理已经销毁且失效的
    powerUps.erase(std::remove_if(powerUps.begin(), powerUps.end(), [](const PowerUp& powerUp) {return powerUp.destroyed && !powerUp.active; }), powerUps.end());

}

void PowerUpManager::ActivatePowerUp(PowerUp* powerUp, BallObject* ball, GameObject* play, PostProcessor* post)
{
    if (powerUp->type == "speed")
    {
        ball->velocity *= 1.2f;
    }
    else if (powerUp->type == "sticky")
    {
        ball->sticky = true;
        play->color = glm::vec4(1.f, 0.5f, 1.f, 1.f);
    }
    else if (powerUp->type == "pass-through")
    {
        ball->passThrough = true;
        ball->color = glm::vec4(1.0f, 0.5f, 0.5f,1.f);
    }
    else if (powerUp->type == "pad-size-increase")
    {
        play->size.x += 50;
    }
    else if (powerUp->type == "confuse")
    {
        if (!post->confuse)
            post->confuse = true;
    }
    else if (powerUp->type == "chaos")
    {
        if (!post->chaos)
            post->chaos = true;
    }
}

void PowerUpManager::Render(SpriteRender& render)
{
    for (PowerUp& it : powerUps)
    {
        if (it.destroyed)
            continue;
        it.DrawCall(render);
    }
}

