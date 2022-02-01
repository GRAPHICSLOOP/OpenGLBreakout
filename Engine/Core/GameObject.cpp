#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec4 color, Texture2D* texture)
{
	Init(pos, size, color, texture);
}

void GameObject::Init(glm::vec2 pos, glm::vec2 size, glm::vec4 color, Texture2D* texture)
{
	destroyed = false;
	this->pos = pos;
	this->size = size;
	this->color = color;
	this->sprite = texture;
}

void GameObject::DrawCall(SpriteRender& render)
{
	if (destroyed)
		return;
	render.Draw(sprite, 0.f, pos, size, color);
}


