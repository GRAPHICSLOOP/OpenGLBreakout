#pragma once

#include <glad/glad.h>

class Texture2D
{
public:
	// texture ID
	GLuint ID;
    GLuint width, height;

    // Texture Format 对象格式和图片格式基本上是相同的
    // ----------------------------------------------

    GLuint internal_Format; // Format of texture object 这个对象的格式
    GLuint image_Format; // Format of loaded image 这个图片本身的格式

    // Texture configuration
    // ----------------------------------------------

    GLuint wrap_S; // Wrapping mode on S axis
    GLuint wrap_T; // Wrapping mode on T axis
    GLuint filter_Min; // Filtering mode if texture pixels < screen pixels
    GLuint filter_Max; // Filtering mode if texture pixels > screen pixels

public:
    // Constructor (sets default texture modes)
    Texture2D();
    ~Texture2D();
    // Binds the texture as the current active GL_TEXTURE_2D texture object

    /**
     * 绑定贴图.
     * 
     * \param index 要激活的texture
     */
    void Bind(GLuint index);
    void Bind();
    // Generates texture from image data

    /**
     * 从内存中生成贴图.
     * 
     * \param width 
     * \param height
     * \param internalFormat 贴图对象格式
     * \param imageFormat 图片本身格式
     * \param data 数据
     */
    void Generate(GLuint width, GLuint height, GLuint internalFormat, GLuint imageFormat, unsigned char* data);
    
};

