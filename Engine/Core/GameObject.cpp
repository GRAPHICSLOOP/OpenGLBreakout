#include "GameObject.h"

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec4 color, Texture2D* texture)
{
	this->pos = pos;
	this->size = size;
	this->color = color;
	this->sprite = texture;
}

void GameObject::DrawCall(SpriteRender& render)
{
	render.Draw(sprite, 0.f, pos, size, color);
}


