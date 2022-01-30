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
	spriteObj = new Sprite();
	ShaderManager* shader = ResourceManager::LoadShader("SpriteShader", "./Engine/Shader/SpriteShader/vsSpriteShader.glsl", "./Engine/Shader/SpriteShader/fsSpriteShader.glsl", nullptr);
	ResourceManager::LoadTexture("Awesomeface", "./Resources/awesomeface.png", true);

	glm::mat4 projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight,-1.f,1.f);
	shader->use();
	shader->SetMatrix("projectionMatrix", projection);
}

void Game::ProcessInput(GLfloat deltaTime)
{

}

void Game::Update(GLfloat detalTime)
{

}

void Game::Render()
{
	spriteObj->Draw(ResourceManager::GetShader("SpriteShader"), ResourceManager::GetTexture("Awesomeface"), 0.f, glm::vec2(100.f), glm::vec2(100.f), glm::vec4(1.f));
}
