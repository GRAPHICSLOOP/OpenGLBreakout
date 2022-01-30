#include "GameLevel.h"

void GameLevel::Init(std::vector<std::vector<GLuint>>& blockData, GLuint levelWidth, GLuint levelHeight)
{
	GLfloat width = blockData[0].size(); // block的数量
	GLfloat height = blockData.size(); // block的数量
	GLfloat unit_width = width / levelWidth; // 每个block的宽
	GLfloat unit_height = height / levelWidth; // 每个block的高

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (blockData[y][x] == 1)
			{

			}
			else if(blockData[y][x] > 1)
			{

			}
		}
	}
}

void GameLevel::LoadLevel(const char* path, GLuint levelWidth, GLuint levelHeight)
{
	
	GLuint blockCode;
	try
	{
		std::string line;
		std::ifstream levelStream(path); // 打开文件
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
			Init(blockData, levelWidth, levelHeight);
	}
	catch (const std::exception&)
	{
		PrintError(ET_READFILE, "Failed to read level files");
	}
}
