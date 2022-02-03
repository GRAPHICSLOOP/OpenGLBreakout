#include "GameLevel.h"

void GameLevel::Init(std::vector<std::vector<GLuint>>& blockData, GLuint levelWidth, GLuint levelHeight)
{
	GLuint width = blockData[0].size(); // block的数量
	GLuint height = blockData.size(); // block的数量
	GLfloat unit_width = (levelWidth / (GLfloat)width); // 每个block的宽
	GLfloat unit_height = (levelHeight / (GLfloat)height); // 每个block的高

	// 初始化bricks对象
	bricks.clear();

	for (GLuint y = 0; y < height; y++)
	{
		for (GLuint x = 0; x < width; x++)
		{
			if (blockData[y][x] == 1)
			{
				glm::vec2 pos(x * unit_width, y * unit_height);
				glm::vec2 size(unit_width, unit_height);
				Texture2D* texture = ResourceManager::LoadTexture("BlockSolid", "./Resources/block_solid.png");

				GameObject obj(pos, size, glm::vec4(1.f), texture);
				obj.isSolid = false;
				bricks.push_back(obj);
			}
			else if(blockData[y][x] > 1)
			{
				glm::vec4 color = glm::vec4(1.0f); // 默认为白色
				if (blockData[y][x] == 2)
					color = glm::vec4(0.2f, 0.6f, 1.0f, 1.f);
				else if (blockData[y][x] == 3)
					color = glm::vec4(0.0f, 0.7f, 0.0f, 1.f);
				else if (blockData[y][x] == 4)
					color = glm::vec4(0.8f, 0.8f, 0.4f, 1.f);
				else if (blockData[y][x] == 5)
					color = glm::vec4(1.0f, 0.5f, 0.0f, 1.f);

				glm::vec2 pos(x * unit_width, y * unit_height);
				glm::vec2 size(unit_width, unit_height);
				Texture2D* texture = ResourceManager::LoadTexture("Block", "./Resources/block.png");

				GameObject obj(pos, size, color, texture);
				obj.isSolid = true;
				bricks.push_back(obj);
			}
		}
	}
}

bool GameLevel::LoadLevel(const char* path, GLfloat levelWidth, GLfloat levelHeight)
{
	
	GLuint blockCode;
	std::ifstream levelStream(path);
	if (!levelStream.is_open())
	{
		PrintError(ET_READFILE, "Failed to read level files");
		return false;
	}


	std::string line;
	std::vector < std::vector<GLuint> > blockData;

	while (std::getline(levelStream, line)) // 循环读取每一行
	{
		std::istringstream sstream(line); // 读取一行到sstream中，以空格裁剪

		std::vector<GLuint> row;
		while (sstream >> blockCode)
		{
			row.push_back(blockCode);
		}

		blockData.push_back(row);
	}

	if (blockData.size() > 0)
		Init(blockData, (GLuint)levelWidth, (GLuint)levelHeight);

	levelStream.close();

	return true;
}

void GameLevel::DrawLevel(SpriteRender& render)
{
	for (GameObject& it : bricks)
	{
		it.DrawCall(render);
	}
}
