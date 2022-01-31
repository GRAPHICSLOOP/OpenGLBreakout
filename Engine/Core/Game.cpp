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


	// 设置渲染状态
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::ProcessInput(GLfloat deltaTime)
{
	if (key[GLFW_KEY_A])
	{
		play.obj->pos.x = glm::clamp(play.obj->pos.x - deltaTime * play.velocity,0.f, (GLfloat)screenWidth);
	}
	
	if (key[GLFW_KEY_D])
	{
		play.obj->pos.x = glm::clamp(play.obj->pos.x + deltaTime * play.velocity, 0.f, (GLfloat)screenWidth - play.obj->size.x);
	}
}

void Game::Update(GLfloat detalTime)
{

}

void Game::Render()
{
	Texture2D* texture = ResourceManager::LoadTexture("Background", "./Resources/background.jpg", true);
	spriteRender.Draw(texture, 0.f, glm::vec2(0.f), glm::vec2(screenWidth, screenHeight), glm::vec4(1.f));
	levels[level].DrawLevel(spriteRender);
	play.obj->DrawCall(spriteRender);
}
