#include "../Headers/Components/SpriteRenderer.h"

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Awake()
{
}

void SpriteRenderer::Start()
{

}

void SpriteRenderer::Update()
{
}

void SpriteRenderer::Destroy()
{
}



Tag SpriteRenderer::ToEnum()
{
	return Tag::SPRITERENDERER;
}

Sprite SpriteRenderer::GetSprite()
{
	return *sprite;
}

void SpriteRenderer::SetSprite(TextureTag textureTag)
{
	
}
