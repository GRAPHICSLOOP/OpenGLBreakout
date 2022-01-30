#include "ResourceManager.h"
// 定义静态变量
std::map<std::string, class Texture2D*> ResourceManager::textures = {};
std::map<std::string, class ShaderManager*> ResourceManager::shaders = {};

void ResourceManager::Clear()
{
	for (auto it : textures)
	{
		glDeleteTextures(1,&it.second->ID);
		delete(it.second);
	}
	textures.clear();

	for (auto it : shaders)
	{
		glDeleteProgram(it.second->ID);
		delete(it.second);
	}
	shaders.clear();
}

Texture2D* ResourceManager::LoadTexture(const char* textureName, const char* texturePath, bool flipImage)
{
	Texture2D* texture2D = GetTexture(textureName);
	if (texture2D != nullptr)
		return texture2D;

	// 0.翻转图片
	stbi_set_flip_vertically_on_load(flipImage);

	// 1.从文件中加载贴图数据
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data == NULL)
	{
		std::cout << "ERROR::LOADTEXTURE::Failed to load texture" << std::endl;
		stbi_image_free(data);
		return nullptr;
	}

	// 2.创建纹理
	texture2D = new Texture2D();
	texture2D->Generate(width, height, GL_RGBA, nrChannels > 3 ? GL_RGBA : GL_RGB, data);
	textures[textureName] = texture2D;

	stbi_image_free(data);
	return texture2D;
}


ShaderManager* ResourceManager::LoadShader(const char* shaderName, const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	ShaderManager* shader = GetShader(shaderName);
	if (shader != nullptr)
		return shader;

	shader = LoadShaderDataFromFile(vertexPath, fragmentPath, geometryPath);
	shaders[shaderName] = shader;
	return shader;
}

Texture2D* ResourceManager::GetTexture(const char* textureName)
{
	auto it = textures.find(textureName);
	if (it != textures.end())
		return textures[textureName];
	else
		return nullptr;

	return nullptr;
}

ShaderManager* ResourceManager::GetShader(const char* shaderName)
{
	auto it = shaders.find(shaderName);
	if (it != shaders.end())
		return shaders[shaderName];
	else
		return nullptr;

	return nullptr;
}

ShaderManager* ResourceManager::LoadShaderDataFromFile(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	// 1.从文件路径中获取 vertex/fragment shader
	std::string vsShaderCode;
	std::string fsShaderCode;
	std::string geShaderCode;

	try
	{
		// 打开文件
		std::ifstream vertexShaderFile(vertexPath);
		std::ifstream fragmentShaderFile(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		
		// 读取文件buffer
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		// 读取完成后关闭
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// 转换到string
		vsShaderCode = vShaderStream.str();
		fsShaderCode = fShaderStream.str();

		// 如果有geShader 那么读取
		if (geometryPath != nullptr)
		{
			std::ifstream geometryShaderFile(geometryPath);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geShaderCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	// 2.创建shader
	ShaderManager* shader = new ShaderManager(vsShaderCode.c_str(), fsShaderCode.c_str(), geometryPath != nullptr ? geShaderCode.c_str() : nullptr);
	return shader;
}
