#include <stdlib.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Game.h"
#include "Core/ResourceManager.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
Game breakOut(SCREEN_WIDTH, SCREEN_HEIGHT);

// 初始化窗口
GLFWwindow* InitWindow(int width, int height);
// 回调-窗口修改大小
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
// 回调-鼠标位置改动
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
// 回调-按键改动
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
	GLFWwindow* window = InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (window == NULL)
		return -1;

	// 时间相关
	// -----------------------------------------------
	GLfloat deltaTime = 0.0f; // 插值
	GLfloat lastTime = 0.0f; // 上一帧时间

	// 初始化
	// -----------------------------------------------
	breakOut.Init();
	glDisable(GL_DEPTH_TEST); // 该游戏不需要深度

	// 游戏循环
	// -----------------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		// 检查各种回调事件，鼠标键盘输入等
		glfwPollEvents();

		// 计算时间
		deltaTime = (GLfloat)glfwGetTime() - lastTime;
		lastTime = (GLfloat)glfwGetTime();

		// 处理输入
		breakOut.ProcessInput(deltaTime);

		// 处理逻辑
		breakOut.Update(deltaTime);

		// 处理渲染
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		breakOut.Render();
	
		// swapbuffer
		glfwSwapBuffers(window);
	}
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

GLFWwindow* InitWindow(int width, int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "BREAKOUT", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "ERROR::InitWindow::Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR::InitWindow::Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return NULL;
	}

	glGetError();

	// 绑定调整窗口函数
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	// 绑定鼠标移动
	glfwSetCursorPosCallback(window, CursorPosCallback);

	// 绑定按键
	glfwSetKeyCallback(window, KeyCallback);

	// 设置是否显示鼠标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	// OPENGL配置
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	return window;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	std::cout << "TIPS::InitWindow::change window size" << std::endl;
	glViewport(0, 0, width, height);
}

void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{

}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window,true);

	if (action == GLFW_PRESS)
		breakOut.key[key] = true;
	else if (action == GLFW_RELEASE)
		breakOut.key[key] = false;
}




