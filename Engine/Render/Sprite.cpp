#include "Sprite.h"

Sprite::Sprite()
{
    InitRenderData();
}

Sprite::~Sprite()
{
    glDeleteVertexArrays(1,&quadVAO);
}

void Sprite::Draw(ShaderManager* shader, Texture2D* texture, GLfloat rotate, glm::vec2 pos, glm::vec2 size, glm::vec4 color)
{
    shader->use();

    // 设置贴图
    texture->Bind(0);
    shader->SetInt("spriteTexture", 0);

    // 创建矩阵
    glm::mat4 posMat4 = glm::translate(glm::mat4(1.f), glm::vec3(pos, 0.f));
    glm::mat4 rotMat4 = glm::rotate(glm::mat4(1.f), glm::radians(rotate), glm::vec3(0.f, 0.f, 1.f));
    glm::mat4 sclMat4 = glm::scale(glm::mat4(1.f), glm::vec3(size, 1.f));
    glm::mat4 modelMat4 = posMat4 * rotMat4 * sclMat4;
    shader->SetMatrix("modelMatrix", modelMat4);

    // 设置颜色
    shader->SetVec4("spriteColor", color);

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Sprite::InitRenderData()
{
    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glBindVertexArray(0);
    
    
}
