#include "Texture2D.h"

Texture2D::Texture2D()
{
	width = 0;
	height = 0;
	internal_Format = GL_RGB;
	image_Format = GL_RGB;
	wrap_S = GL_REPEAT;
	wrap_T = GL_REPEAT;
	filter_Min = GL_LINEAR;
	filter_Max = GL_LINEAR;

	glGenTextures(1, &ID);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &ID);
}

void Texture2D::Bind(GLuint index)
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::Generate(GLuint width, GLuint height,GLuint internalFormat, GLuint imageFormat,unsigned char* data)
{
	this->width = width;
	this->height = height;
	this->internal_Format = internalFormat;
	this->image_Format = imageFormat;

	// 设置缓冲数据
	Bind(0);
	glTexImage2D(GL_TEXTURE_2D, 0, internal_Format, width, height, 0, image_Format, GL_UNSIGNED_BYTE, data);

	// 设置缓冲属性
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_Max);

	// 解除绑定
	glBindTexture(GL_TEXTURE_2D, 0);
}


