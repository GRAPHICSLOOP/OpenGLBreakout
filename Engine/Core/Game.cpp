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
	GameLevel one; one.LoadLevel("./Resources/levels/one.txt", screenWidth, screenHeight * 0.5);
	GameLevel two; two.LoadLevel("./Resources/levels/two.txt", screenWidth, screenHeight * 0.5);
	GameLevel three; three.LoadLevel("./Resources/levels/three.txt", screenWidth, screenHeight * 0.5);
	GameLevel four; four.LoadLevel("./Resources/levels/four.txt", screenWidth, screenHeight * 0.5);
	levels.push_back(one);
	levels.push_back(two);
	levels.push_back(three);
	levels.push_back(four);
	level = 0;

	ShaderManager* shader = ResourceManager::LoadShader("SpriteShader", "./Engine/Shader/SpriteShader/vsSpriteShader.glsl", "./Engine/Shader/SpriteShader/fsSpriteShader.glsl", nullptr);
	glm::mat4 projection = glm::ortho(0.0f, (GLfloat)screenWidth, (GLfloat)screenHeight, 0.0f, -1.f, 1.f);
	shader->use();
	shader->SetMatrix("projectionMatrix", projection);
	spriteRender.Init(shader);
	
	// 初始化玩家
	play.Init(glm::vec2(0.f, screenHeight - 20.f), ResourceManager::LoadTexture("Paddle", "./Resources/paddle.png"));

	// 初始化球
	ballObj.Init(glm::vec2(play.obj->size.x / 2.f - 10.f, screenHeight - 40.f), 10.f, glm::vec4(1.f), ResourceManager::LoadTexture("Awesomeface", "./Resources/awesomeface.png"));

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
	ballObj.Move(detalTime, screenWidth);
	DoCollisionCheck();
}

void Game::Render()
{
	Texture2D* texture = ResourceManager::LoadTexture("Background", "./Resources/background.jpg", true);
	spriteRender.Draw(texture, 0.f, glm::vec2(0.f), glm::vec2(screenWidth, screenHeight), glm::vec4(1.f));
	levels[level].DrawLevel(spriteRender);
	play.obj->DrawCall(spriteRender);
	ballObj.DrawCall(spriteRender);
}

bool Game::CheckCollision(GameObject* one, GameObject* two)
{
	// 比较不精确的碰撞检测
	/*GLboolean xCollision = one->pos.x + one->size.x >= two->pos.x && two->pos.x + two->size.x >= one->pos.x;
	GLboolean yCollision = one->pos.y + one->size.y >= two->pos.y && two->pos.y + two->size.y >= one->pos.y;

	return xCollision && yCollision;*/

	// 1.获取球中心点和box的边长和中心点
	// --------------------------------------------
	glm::vec2 center = one->pos + (one->size / 2.f);
	glm::vec2 aabb_half_extents = two->size / 2.f;
	glm::vec2 aabb_center = two->pos + aabb_half_extents;

	// 2.计算出球落在box的最近交点
	// --------------------------------------------

	glm::vec2 dif = center - aabb_center; // 球心和box心的向量
	glm::vec2 clamped = glm::clamp(dif, -aabb_half_extents, aabb_half_extents); // clamp的作用，我们只关心落在box内的点，因此将落在外面的统统去掉，减小多余的判断
	glm::vec2 closest = aabb_center + clamped; // 获取最近点
	dif = closest - center; // 获取球心到最近点的向量
	return glm::length(dif) < (one->size.x / 2.f); // 若最近点向量的长度小于球半径 那么说明球已经在box内了
}

void Game::DoCollisionCheck()
{
	for (GameObject& it : levels[level].bricks)
	{
		if (it.destroyed)
			continue;

		if (CheckCollision(&ballObj, &it))
		{
			it.destroyed = true;
		}
	}
}
