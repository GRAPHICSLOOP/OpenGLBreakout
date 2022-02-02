#pragma once

#include <glad/glad.h>
#include "../Core/ShaderManager.h"
#include "../Core/Texture2D.h"

class PostProcessor
{
private:
	GLuint MSFBO; // 多重抗锯齿buf
	GLuint FBO; // 帧buf
	GLuint RBO; // 渲染buf
	GLuint VAO;
	GLuint width, height;

	Texture2D* texture;
	ShaderManager* shader;

public:
	GLboolean confuse, chaos, shake;
	GLfloat shakeTime;

public:
	~PostProcessor();

	/**
	 * 初始化.
	 * 
	 * \param shader
	 * \param width 屏幕宽
	 * \param height 屏幕高
	 */
	void Init(ShaderManager* shader, GLuint width, GLuint height);

	/**
	 * 逻辑处理.
	 * 
	 * \param detalTime
	 */
	void update(GLfloat detalTime);

	void BeginRender();
	void EndRender();
	void Render(GLfloat time);
	
private:
	// 初始化渲染数据
	void InitRenderData();
};

