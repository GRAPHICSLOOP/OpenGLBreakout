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

class ResourceManager
{
public:
	static std::map<std::string,class Texture2D*> textures;
	static std::map<std::string,class ShaderManager*> shaders;

public:
	static void Clear();
	static Texture2D* LoadTexture(std::string textureName, const std::string& texturePath, bool flipImage =false);
	static ShaderManager* LoadShader(const std::string shaderName, const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath);
	static Texture2D* GetTexture(const std::string textureName);
	static ShaderManager* GetShader(const std::string shaderName);
private:
	static const char* LoadShaderDataFromFile(const std::string& filePath);
};

