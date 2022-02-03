#include "TextRender.h"

void TextRender::Init(GLuint width, GLuint height)
{

	// 初始化shader
	shader = ResourceManager::LoadShader("TextShader", "./Engine/Shader/Font/vsFontShader.glsl", "./Engine/Shader/Font/fsFontShader.glsl", nullptr);
	glm::mat4 proj = glm::ortho(0.f, (GLfloat)width, (GLfloat)height, 0.f);
	shader->use();
	shader->SetMatrix("projection", proj);
	shader->SetInt("textTexture", 0);

	// 初始化渲染配置
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void*)0);
	glBindVertexArray(0);
}

void TextRender::Load(const char* fontFile, GLuint fontSize)
{
	characters.clear();
	
	// 初始化FT库
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		PrintError(ET_FREETYPE, "Could not init FreeType Library");

	// 初始化字形
	FT_Face face;
	if (FT_New_Face(ft, fontFile, 0, &face))
		PrintError(ET_FREETYPE, "Failed to load font");

	// 设置字形大小
	FT_Set_Pixel_Sizes(face, 0, fontSize);

	// 关闭4字节对齐方式 改为单字节对齐
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			PrintError(ET_FREETYPE, "Failed to load Glyph");
			continue;
		}

		// 创建贴图
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D,0, GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer);

		// 设置贴图属性
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character charater = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};

		characters[c] = charater;
	}
    
}

void TextRender::Render(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color)
{
	// 激活对应的渲染状态
	shader->use();
	shader->SetVec4("textColor", color);
	glActiveTexture(GL_TEXTURE0);

	// 遍历文本中的字符
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];

		GLfloat xpos = x + ch.bearing.x * scale;
		GLfloat ypos = y + (this->characters['H'].bearing.y - ch.bearing.y) * scale;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;

		// 对每个字符更新VBO
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 0.0f },

			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f }
		};

		// 在四边形上绘制纹理
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		// 绘制四边形
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (ch.advance >> 6) * scale;

	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
