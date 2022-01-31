#include "Game.h"


Game::Game(GLuint width, GLuint height)
{
	screenHeight = height;
	screenWidth = width;
	Init();
}

Game::~Game()
{

}

void Game::Init()
{
	if (!level.LoadLevel("./Resources/level/level_1.txt", screenWidth, screenHeight * 0.5))
		return;

	ShaderManager* shader = ResourceManager::LoadShader("SpriteShader", "./Engine/Shader/SpriteShader/vsSpriteShader.glsl", "./Engine/Shader/SpriteShader/fsSpriteShader.glsl", nullptr);
	glm::mat4 projection = glm::ortho(0.0f, (GLfloat)screenWidth, (GLfloat)screenHeight, 0.0f, -1.f, 1.f);
	shader->use();
	shader->SetMatrix("projectionMatrix", projection);
	spriteRender.shader = shader;
	
}

void Game::ProcessInput(GLfloat deltaTime)
{

}

void Game::Update(GLfloat detalTime)
{

}

void Game::Render()
{
	level.DrawLevel(spriteRender);
}
