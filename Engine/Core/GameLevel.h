#pragma once

#include <glad/glad.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "CommonTool.h"

class GameLevel
{
public:

	/**
	 * 初始化level.
	 * 
	 * \param titleData level数据
	 * \param levelWidth level总宽
	 * \param levelHeight level总高
	 */
	void Init(std::vector<std::vector<GLuint>> & blockData,GLuint levelWidth,GLuint levelHeight);


	/**
	 * 从文件中载入level.
	 * 
	 * \param path level文件位置
	 * \param levelWidth
	 * \param levelHeight
	 */
	void LoadLevel(const char* path, GLuint levelWidth, GLuint levelHeight);
};

