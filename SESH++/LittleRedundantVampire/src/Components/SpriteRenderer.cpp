#include "../Headers/Components/SpriteRenderer.h"
#include <iostream>
using namespace std;
using namespace sf;

SpriteRenderer::~SpriteRenderer()
{
	delete sprite;
	sprite = nullptr;

	delete texture;
	texture = nullptr;
}

void SpriteRenderer::Awake()
{

}

void SpriteRenderer::Start()
{

}

void SpriteRenderer::Update(Time* timePerFrame)
{
	//TODO:Make sure that the position is NOT OUTDATED
	sprite->setPosition(*gameObject->position);
}

void SpriteRenderer::Destroy()
{
	SpriteRenderer::~SpriteRenderer();
}

ComponentTag SpriteRenderer::ToEnum()
{
	return ComponentTag::SPRITERENDERER;
}

Sprite SpriteRenderer::GetSprite()
{
	return *sprite;
}

void SpriteRenderer::SetSprite(TextureTag textureTag)
{
	texture = Asset::GetInstance()->GetTexture(textureTag);
	sprite->setTexture(*texture);
}
