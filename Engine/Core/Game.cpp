#include "Game.h"


Game::Game(GLuint width, GLuint height)
{
	screenHeight = height;
	screenWidth = width;
}

Game::~Game()
{

}

void Game::Init()
{
	// 加载关卡
	GameLevel one; one.LoadLevel("./Resources/levels/one.txt", (GLfloat)screenWidth, (GLfloat)screenHeight * 0.5f);
	GameLevel two; two.LoadLevel("./Resources/levels/two.txt", (GLfloat)screenWidth, (GLfloat)screenHeight * 0.5f);
	GameLevel three; three.LoadLevel("./Resources/levels/three.txt", (GLfloat)screenWidth, (GLfloat)screenHeight * 0.5f);
	GameLevel four; four.LoadLevel("./Resources/levels/four.txt", (GLfloat)screenWidth, (GLfloat)screenHeight * 0.5f);
	levels.push_back(one);
	levels.push_back(two);
	levels.push_back(three);
	levels.push_back(four);
	level = 0;

	// 创建spriteShader
	ShaderManager* spriteShader = ResourceManager::LoadShader("SpriteShader", "./Engine/Shader/SpriteShader/vsSpriteShader.glsl", "./Engine/Shader/SpriteShader/fsSpriteShader.glsl", nullptr);
	glm::mat4 projection = glm::ortho(0.0f, (GLfloat)screenWidth, (GLfloat)screenHeight, 0.0f, -1.f, 1.f);
	spriteShader->use();
	spriteShader->SetMatrix("projectionMatrix", projection);
	spriteRender.Init(spriteShader);
	
	// 初始化玩家
	play.Init(glm::vec2(0.f, screenHeight - 20.f), ResourceManager::LoadTexture("Paddle", "./Resources/paddle.png"));

	// 初始化球
	ballObj.Init(glm::vec2(play.obj->size.x / 2.f - 10.f, screenHeight - 40.f), 10.f, glm::vec4(1.f), ResourceManager::LoadTexture("Awesomeface", "./Resources/awesomeface.png"));

	// 初始化粒子
	particleGenerator.Init(500, ResourceManager::LoadTexture("Particle", "./Resources/particle.png"));

	// 创建postShader
	ShaderManager* postShader = ResourceManager::LoadShader("PostShader", "./Engine/Shader/PostProcess/vsPostProcess.glsl", "./Engine/Shader/PostProcess/fsPostProcess.glsl", nullptr);

	// 初始化后期处理
	postProcessor.Init(postShader, screenWidth, screenHeight);

	// 初始化音频
	iSoundEngine = irrklang::createIrrKlangDevice();
	iSoundEngine->play2D("./Resources/audio/breakout.mp3", true);

	// 初始化文字
	textRender.Init(screenWidth, screenHeight);
	textRender.Load("./Resources/Font/arial.ttf", 24);

	// 设置渲染状态
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::ProcessInput(GLfloat deltaTime)
{
	if (key[GLFW_KEY_A])
	{
		play.obj->pos.x = glm::clamp(play.obj->pos.x - deltaTime * play.velocity,0.f, (GLfloat)screenWidth);

		if (ballObj.stuck)
			ballObj.pos.x = glm::clamp(ballObj.pos.x - deltaTime * play.velocity, 0.f, (GLfloat)screenWidth);
	}
	
	if (key[GLFW_KEY_D])
	{
		play.obj->pos.x = glm::clamp(play.obj->pos.x + deltaTime * play.velocity, 0.f, (GLfloat)screenWidth - play.obj->size.x);
		if (ballObj.stuck)
			ballObj.pos.x = glm::clamp(ballObj.pos.x + deltaTime * play.velocity, 0.f, (GLfloat)screenWidth - ballObj.size.x);
	}

	if (key[GLFW_KEY_SPACE])
	{
		ballObj.stuck = false;
	}
}

void Game::Update(GLfloat detalTime)
{
	ballObj.Move(detalTime, (GLfloat)screenWidth);
	DoCollisionCheck();

	if (ballObj.pos.y > screenHeight)
	{
		ResetLevel();
		ResetPlay();
	}

	// 更新粒子
	particleGenerator.Update(detalTime, &ballObj);

	// 更新后期
	postProcessor.update(detalTime);

	// 更新道具
	powerUpManager.Update(detalTime,&ballObj,play.obj,&postProcessor);
}

void Game::Render()
{
	postProcessor.BeginRender();
	Texture2D* texture = ResourceManager::LoadTexture("Background", "./Resources/background.jpg", true);
	spriteRender.Draw(texture, 0.f, glm::vec2(0.f), glm::vec2(screenWidth, screenHeight), glm::vec4(1.f));
	levels[level].DrawLevel(spriteRender);
	play.obj->DrawCall(spriteRender);
	particleGenerator.DrawCall(&spriteRender);
	ballObj.DrawCall(spriteRender);
	powerUpManager.Render(spriteRender);
	postProcessor.EndRender();
	postProcessor.Render((GLfloat)glfwGetTime());

	textRender.Render("Level:1", 10.f, 10.f);
}

Collision Game::CheckCollision(GameObject* one, GameObject* two)
{
	// 1.获取球中心点和box的边长和中心点
	// --------------------------------------------
	glm::vec2 center = one->pos + (one->size / 2.f);
	glm::vec2 aabb_half_extents = two->size / 2.f;
	glm::vec2 aabb_center = two->pos + aabb_half_extents;

	// 2.计算出球落在box的最近交点
	// --------------------------------------------

	glm::vec2 dir = center - aabb_center; // 球心和box心的向量
	glm::vec2 clamped = glm::clamp(dir, -aabb_half_extents, aabb_half_extents); // clamp的作用，我们只关心落在box内的点，因此将落在外面的统统去掉，减小多余的判断
	glm::vec2 closest = aabb_center + clamped; // 获取最近点
	dir = closest - center; // 获取球心到最近点的向量
	if (glm::length(dir) < (one->size.x / 2.f)) // 若最近点向量的长度小于球半径 那么说明球已经在box内了
	{
		return std::make_tuple(true, CheckVectionDirection(-dir), dir);
	}
	else
	{
		return std::make_tuple(false, (Direction)0, glm::vec2(1.f));
	}
}

void Game::DoCollisionCheck()
{
	// 与方块检查碰撞
	for (GameObject& it : levels[level].bricks)
	{
		if (it.destroyed)
			continue;

		Collision collision = CheckCollision(&ballObj, &it);
		if (std::get<0>(collision))
		{
			glm::vec2 dif = glm::abs(std::get<2>(collision));
			if (it.isSolid)
			{
				it.destroyed = true;
			}
			else
			{
				postProcessor.shakeTime = 0.05f;
				postProcessor.shake = true;
			}

			// 生成道具
			powerUpManager.SpawnPowerUps(it);

			// 若设置了球可穿越
			if (ballObj.passThrough && it.isSolid)
				continue;
			switch (std::get<1>(collision))
			{
			case Direction::UP :
				ballObj.pos.y -= ballObj.radius - dif.y;
				ballObj.velocity.y = -ballObj.velocity.y;
				break;
			case Direction::DOWN :
				ballObj.pos.y += ballObj.radius - dif.y;
				ballObj.velocity.y = -ballObj.velocity.y;
				break;
			case Direction::RIGHT :
				ballObj.pos.x += ballObj.radius - dif.x;
				ballObj.velocity.x = -ballObj.velocity.x;
				break;
			case Direction::LEFT :
				ballObj.pos.x -= ballObj.radius - dif.x;
				ballObj.velocity.x = -ballObj.velocity.x;
				break;
			default:
				break;
			}

			break;
		}
	}

	// 与玩家检查碰撞
	{
		Collision collision = CheckCollision(&ballObj, play.obj);
		if (std::get<0>(collision))
		{
			if (ballObj.sticky)
			{
				ballObj.stuck = ballObj.sticky;
			}

			float centerBoard = play.obj->pos.x + (play.obj->size.x / 2.f);
			float distance = ballObj.pos.x + ballObj.radius - centerBoard;
			float persent = distance / (play.obj->size.x / 2.f);

			// 生成一个新的方向，当时不改变原来力的大小
			float len = glm::length(ballObj.velocity);
			glm::vec2 newDirection = ballObj.velocity;
			newDirection.x = INIT_BALL_VELOCITY.x * persent * 2.f;
			newDirection.y = -glm::abs(newDirection.y); // 防止卡住
			ballObj.velocity = glm::normalize(newDirection) * len;
		}
	}
	

	// 道具与玩家碰撞
	for (PowerUp& it : powerUpManager.powerUps)
	{
		if (it.destroyed)
			continue;
		Collision collision = CheckCollision(&it, play.obj);
		if (std::get<0>(collision))
		{
			powerUpManager.ActivatePowerUp(&it, &ballObj, play.obj, &postProcessor);
			it.destroyed = true;
			it.active = true;
		}
	}
}

Direction Game::CheckVectionDirection(glm::vec2 target)
{
	glm::vec2 dir[4] = {
		glm::vec2(0.f,-1.f),
		glm::vec2(1.f,0.f),
		glm::vec2(0.f,1.f),
		glm::vec2(-1.f,0.f)
	};

	float max = 0.f;
	int result = -1;
	for (int i = 0; i < 4; i++)
	{
		float d = glm::dot(target, dir[i]);
		if (d > max)
		{
			max = d;
			result = i;
		}
	}
	
	return (Direction)result;
}

void Game::ResetLevel()
{
	GameLevel resetLevel;
	switch (level)
	{
	case 0:
		levels[0].LoadLevel("./Resources/levels/one.txt", (GLfloat)screenWidth, (GLfloat)screenHeight * 0.5f);
		break;
	case 1:
		levels[1].LoadLevel("./Resources/levels/two.txt", (GLfloat)screenWidth, (GLfloat)screenHeight * 0.5f);
		break;
	case 2:
		levels[2].LoadLevel("./Resources/levels/three.txt", (GLfloat)screenWidth, (GLfloat)screenHeight * 0.5f);
		break;
	case 3:
		levels[3].LoadLevel("./Resources/levels/four.txt", (GLfloat)screenWidth, (GLfloat)screenHeight * 0.5f);
		break;
	default:
		break;
	}
}

void Game::ResetPlay()
{
	// 初始化玩家
	play.Init(glm::vec2(0.f, screenHeight - 20.f), ResourceManager::LoadTexture("Paddle", "./Resources/paddle.png"));

	// 初始化球
	ballObj.Init(glm::vec2(play.obj->size.x / 2.f - 10.f, screenHeight - 40.f), 10.f, glm::vec4(1.f), ResourceManager::LoadTexture("Awesomeface", "./Resources/awesomeface.png"));
}
