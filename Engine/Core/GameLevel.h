#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "CommonTool.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "../Render/SpriteRender.h"

class GameLevel
{
public:
	std::vector<GameObject> bricks;

private:
	
	/**
	 * 初始化level.
	 * 
	 * \param titleData level数据
	 * \param levelWidth level总宽
	 * \param levelHeight level总高
	 */
	void Init(std::vector<std::vector<GLuint>> & blockData,GLuint levelWidth,GLuint levelHeight);

public:

	/**
	 * 从文件中载入level.
	 * 
	 * \param path level文件位置
	 * \param levelWidth
	 * \param levelHeight
	 */
	bool LoadLevel(const char* path, GLuint levelWidth, GLuint levelHeight);

	/**
	 * 渲染场景.
	 * 
	 * \param renderer 渲染器
	 */
	void DrawLevel(SpriteRender& render);
};

