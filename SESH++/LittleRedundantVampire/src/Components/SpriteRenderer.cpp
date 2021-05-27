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

	delete textureRect;
	textureRect = nullptr;

	if (currentImage != nullptr)
	{
		delete currentImage;
		currentImage = nullptr;
	}

	if (imageCount != nullptr)
	{
		delete imageCount;
		imageCount = nullptr;
	}

	delete flipped;
	flipped = nullptr;
}

/// <summary>
/// Spriterenderer Constructor for non-spritesheets
/// </summary>
/// <param name="textureTag"></param>
SpriteRenderer::SpriteRenderer(TextureTag textureTag)
{
	texture = new Texture(*Asset::GetInstance()->FetchTexture(textureTag));
	sprite = new Sprite(*texture);

	textureRect = new IntRect();
	textureRect->width = texture->getSize().x;
	textureRect->height = texture->getSize().y;
	float width = texture->getSize().x;
	float heigt = texture->getSize().y;

	sprite->setOrigin(Vector2f(width / 2, heigt / 2));

	flipped = new bool;
	*flipped = false;
	drawComponent = true;
}

/// <summary>
/// Spriterenderer Constructor for spritesheets
/// </summary>
/// <param name="textureTag"></param>
SpriteRenderer::SpriteRenderer(TextureTag textureTag, Vector2u currentImage, Vector2u imageCount)
{
	texture = new Texture(*Asset::GetInstance()->FetchTexture(textureTag));
	sprite = new Sprite(*texture);
	this->currentImage = new Vector2u(currentImage);
	this->imageCount = new Vector2u(imageCount);

	flipped = new bool;
	*flipped = false;

	textureRect = new IntRect();
	// We define the width and height on our textureRectangle compared to the png-file, so the sprite gets the right size.

	textureRect->width = texture->getSize().x / float(this->imageCount->x);
	textureRect->height = texture->getSize().y / float(this->imageCount->y);

	// The standard width is always equal to the normal width.
	textureRect->width = abs(textureRect->width);

	sprite->setTextureRect(*textureRect);
	sprite->setOrigin(Vector2f(textureRect->width / 2, textureRect->height / 2));
	drawComponent = true;
}

void SpriteRenderer::Awake()
{
}

void SpriteRenderer::Start()
{
	sprite->setPosition(*gameObject->GetPosition());
}

void SpriteRenderer::Update(Time* timePerFrame)
{
	//TODO:* Make sure that the position is NOT OUTDATED
	if (sprite->getPosition() != *gameObject->GetPosition())
	{
		sprite->setPosition(*gameObject->GetPosition());
	}
}

void SpriteRenderer::Destroy()
{
	SpriteRenderer::~SpriteRenderer();
}

ComponentTag SpriteRenderer::ToEnum()
{
	return ComponentTag::SPRITERENDERER;
}

Sprite SpriteRenderer::GetSprite() const
{
	return *sprite;
}

void SpriteRenderer::FlipSprite()
{
	sprite->scale(-1, 1);
}

Texture SpriteRenderer::GetTexture() const
{
	return *texture;
}

IntRect SpriteRenderer::GetTextureRect() const
{
	return *textureRect;
}

Vector2u SpriteRenderer::GetImageCount() const
{
	return *imageCount;
}

void SpriteRenderer::SetTextureRect(IntRect textureRect)
{
	*this->textureRect = textureRect;
	sprite->setTextureRect(textureRect);
}

bool* SpriteRenderer::GetFlipped() const
{
	return flipped;
}