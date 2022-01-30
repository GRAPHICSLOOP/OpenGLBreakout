#pragma once
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "Texture2D.h"
#include "ShaderManager.h"
#include "stb_image/stb_image.h"
#include "CommonTool.h"

class ResourceManager
{
public:
	static std::map<std::string ,class Texture2D*> textures;
	static std::map<std::string ,class ShaderManager*> shaders;

public:
	static void Clear();

	static Texture2D* LoadTexture(const char* textureName, const char* texturePath, bool flipImage =false);
	static ShaderManager* LoadShader(const char* shaderName, const char* vertexPath, const char* fragmentPath, const char* geometryPath);
	static Texture2D* GetTexture(const char* textureName);
	static ShaderManager* GetShader(const char* shaderName);
private:

	static ShaderManager* LoadShaderDataFromFile(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
};

