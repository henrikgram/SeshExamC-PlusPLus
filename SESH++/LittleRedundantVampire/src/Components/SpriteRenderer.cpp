#include "SpriteRenderer.h"
#include <iostream>
using namespace std;
using namespace sf;

SpriteRenderer::~SpriteRenderer()
{
	delete sprite;
	sprite = nullptr;

	delete texture;
	texture = nullptr;

	delete TextureRect;
	TextureRect = nullptr;

	delete currentImage;
	currentImage = nullptr;

	delete imageCount;
	imageCount = nullptr;
}

SpriteRenderer::SpriteRenderer()
{

}

SpriteRenderer::SpriteRenderer(Vector2u currentImage, Vector2u imageCount)
{
	//currentImage = new Vector2u(1, 1);
	this->currentImage = &currentImage;
	this->imageCount = &currentImage;
	//imageCount = new Vector2u(4, 3);

	isSpriteSheet = true;
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
	sprite->setPosition(*gameObject->GetPosition());
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

void SpriteRenderer::FlipSprite()
{
	sprite->scale(-1, 1);
}

Texture SpriteRenderer::GetTexture()
{
	return *texture;
}

bool SpriteRenderer::GetIsSpriteSheet()
{
	return isSpriteSheet;
}

void SpriteRenderer::SetSprite(TextureTag textureTag)
{
	//TODO: This might work better if we make a constructor for the SpriteRenderer class and pass a texturetag to this 
	//so we don't have to call SetSprite outside of this class. 
	texture = Asset::GetInstance()->GetTexture(textureTag);

	if (isSpriteSheet)
	{
		sprite->setTexture(*texture);

		//Vi skal definere bredden og højden på vores textureRectangle ift til png-filen, så sprite for den rigtige dimension.
		TextureRect->width = texture->getSize().x / float(imageCount->x);
		TextureRect->height = texture->getSize().y / float(imageCount->y);

		//Standard bredden er altid lige med den normale bredde.
		TextureRect->width = abs(TextureRect->width);

		sprite->setTextureRect(*TextureRect);
		sprite->setOrigin(Vector2f(TextureRect->width / 2, TextureRect->height / 2));
	}
	else
	{
		sprite->setTexture(*texture);

		float width = texture->getSize().x;
		float heigt = texture->getSize().y;

		sprite->setOrigin(Vector2f(width/2, heigt/2));
	}
}

void SpriteRenderer::SetTextureRect(IntRect& textureRect)
{
	this->TextureRect = &textureRect;
	sprite->setTextureRect(*TextureRect);
}
