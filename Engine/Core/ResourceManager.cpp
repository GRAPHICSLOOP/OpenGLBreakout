#include "ResourceManager.h"

Texture2D* ResourceManager::LoadTexture(std::string textureName, const std::string& texturePath, bool flipImage)
{
	Texture2D* texture2D = GetTexture(textureName);
	if (texture2D != nullptr)
		return texture2D;

	// 0.翻转图片
	stbi_set_flip_vertically_on_load(flipImage);

	// 1.从文件中加载贴图数据
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data == NULL)
	{
		std::cout << "ERROR::LOADTEXTURE::Failed to load texture" << std::endl;
		stbi_image_free(data);
		return nullptr;
	}

	// 2.创建纹理
	texture2D = new Texture2D();
	texture2D->Generate(width, height, data);
	textures.insert(std::pair<std::string,class Texture2D*>(textureName, texture2D));

	stbi_image_free(data);
	return texture2D;
}

ShaderManager* ResourceManager::LoadShader(const std::string shaderName, const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
{
	ShaderManager* shader = GetShader(shaderName);
	if (shader != nullptr)
		return shader;

	const char* vsSource = LoadShaderDataFromFile(vertexPath);
	const char* fsSource = LoadShaderDataFromFile(fragmentPath);
	const char* geSource = LoadShaderDataFromFile(geometryPath);

	// 2.创建shader
	shader = new ShaderManager(vsSource, fsSource, geSource);
	shaders.insert(std::pair<std::string,class ShaderManager*>(shaderName, shader));
	return shader;
}

Texture2D* ResourceManager::GetTexture(const std::string textureName)
{
	auto it = textures.find(textureName);
	if (it != textures.end())
		return textures[textureName];
	else
		return nullptr;

	return nullptr;
}

ShaderManager* ResourceManager::GetShader(const std::string shaderName)
{
	auto it = shaders.find(shaderName);
	if (it != shaders.end())
		return shaders[shaderName];
	else
		return nullptr;

	return nullptr;
}

const char* ResourceManager::LoadShaderDataFromFile(const std::string& filePath)
{
	// 1.从文件路径中获取 vertex/fragment shader
	std::string shaderCode;
	std::ifstream shaderFile;

	// 抛出异常
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// 打开文件
		shaderFile.open(filePath);

		std::stringstream shaderStream;
		// 读取文件内容到数据流中
		shaderStream << shaderFile.rdbuf();

		// 转换为string
		shaderCode = shaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return shaderCode.c_str();
}
