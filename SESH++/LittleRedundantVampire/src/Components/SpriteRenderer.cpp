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
	sprite = new Sprite();
	Texture* texture = new Texture;
	//texture = Asset::GetInstance()->GetTexture(textureTag);

	texture->loadFromFile("Asset_2/VampireOzzyStill.png");
	sprite->setTexture(*texture);
}
