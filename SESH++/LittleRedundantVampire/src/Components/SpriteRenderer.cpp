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

	delete flipped;
	flipped = nullptr;
}

//SpriteRenderer::SpriteRenderer()
//{
//
//}
//
//SpriteRenderer::SpriteRenderer(Vector2u currentImage, Vector2u imageCount)
//{
//	//currentImage = new Vector2u(1, 1);
//	/*this->currentImage = &currentImage;
//	this->imageCount = &currentImage;*/
//	//imageCount = new Vector2u(4, 3);
//	//isSpriteSheet = true;
//
//}

/// <summary>
/// Spriterenderer Constructor for non-spritesheets
/// </summary>
/// <param name="textureTag"></param>
SpriteRenderer::SpriteRenderer(TextureTag textureTag)
{
	//TODO: This enture constructor may be unnecessary if we put everything up in a spritesheet.
	texture = new Texture(*Asset::GetInstance()->GetTexture(textureTag));
	sprite = new Sprite(*texture);
	//TODO: These following two are only used for spritesheets so can we avoid them taking up space in the heap memory?
	this->currentImage = new Vector2u;
	this->imageCount = new Vector2u;
	isSpriteSheet = false;

	TextureRect = new IntRect();
	TextureRect->width = texture->getSize().x;
	TextureRect->height = texture->getSize().y;
	float width = texture->getSize().x;
	float heigt = texture->getSize().y;

	sprite->setOrigin(Vector2f(width / 2, heigt / 2));

	flipped = new bool;
	*flipped = false;
}

/// <summary>
/// Spriterenderer Constructor for spritesheets
/// </summary>
/// <param name="textureTag"></param>
SpriteRenderer::SpriteRenderer(TextureTag textureTag, Vector2u currentImage, Vector2u imageCount)
{
	texture = new Texture(*Asset::GetInstance()->GetTexture(textureTag));
	sprite = new Sprite(*texture);
	this->currentImage = new Vector2u(currentImage);
	this->imageCount = new Vector2u(imageCount);

	flipped = new bool;
	*flipped = false;
	
	isSpriteSheet = true;

	TextureRect = new IntRect();
	//Vi skal definere bredden og h�jden p� vores textureRectangle ift til png-filen, s� sprite for den rigtige dimension.
	TextureRect->width = texture->getSize().x / float(this->imageCount->x);
	TextureRect->height = texture->getSize().y / float(this->imageCount->y);

	//Standard bredden er altid lige med den normale bredde.
	TextureRect->width = abs(TextureRect->width);

	sprite->setTextureRect(*TextureRect);
	sprite->setOrigin(Vector2f(TextureRect->width / 2, TextureRect->height / 2));
}

void SpriteRenderer::Awake()
{
	//if (isSpriteSheet)
	//{
	//	//Vi skal definere bredden og h�jden p� vores textureRectangle ift til png-filen, s� sprite for den rigtige dimension.
	//	TextureRect->width = texture->getSize().x / float(imageCount->x);
	//	TextureRect->height = texture->getSize().y / float(imageCount->y);

	//	//Standard bredden er altid lige med den normale bredde.
	//	TextureRect->width = abs(TextureRect->width);

	//	sprite->setTextureRect(*TextureRect);
	//	sprite->setOrigin(Vector2f(TextureRect->width / 2, TextureRect->height / 2));
	//}
	//else
	//{
	//	TextureRect->width = texture->getSize().x;
	//	TextureRect->height = texture->getSize().y;
	//	float width = texture->getSize().x;
	//	float heigt = texture->getSize().y;

	//	sprite->setOrigin(Vector2f(width / 2, heigt / 2));
	//}
}

void SpriteRenderer::Start()
{
	sprite->setPosition(*gameObject->GetPosition());
}

void SpriteRenderer::Update(Time* timePerFrame)
{
	//TODO:Make sure that the position is NOT OUTDATED
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

//void SpriteRenderer::SetSprite(TextureTag textureTag)
//{
//	//TODO: This might work better if we make a constructor for the SpriteRenderer class and pass a texturetag to this
//	//so we don't have to call SetSprite outside of this class.
//	texture = Asset::GetInstance()->GetTexture(textureTag);
//
//	if (isSpriteSheet)
//	{
//		sprite->setTexture(*texture);
//
//		//Vi skal definere bredden og h�jden p� vores textureRectangle ift til png-filen, s� sprite for den rigtige dimension.
//		TextureRect->width = texture->getSize().x / float(imageCount->x);
//		TextureRect->height = texture->getSize().y / float(imageCount->y);
//
//		//Standard bredden er altid lige med den normale bredde.
//		TextureRect->width = abs(TextureRect->width);
//
//		sprite->setTextureRect(*TextureRect);
//		sprite->setOrigin(Vector2f(TextureRect->width / 2, TextureRect->height / 2));
//	}
//	else
//	{
//		sprite->setTexture(*texture);
//
//		float width = texture->getSize().x;
//		float heigt = texture->getSize().y;
//
//		sprite->setOrigin(Vector2f(width / 2, heigt / 2));
//	}
//}

void SpriteRenderer::SetTextureRect(IntRect& textureRect)
{
	this->TextureRect = &textureRect;
	sprite->setTextureRect(*TextureRect);
}

bool* SpriteRenderer::GetFlipped()
{
	return flipped;
}
