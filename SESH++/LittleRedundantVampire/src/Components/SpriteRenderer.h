#pragma once
#include "../Component.h"
#include "../Enum/TextureTag.h"
#include "../Asset.h"
using namespace sf;

class SpriteRenderer : public Component
{
public:

	~SpriteRenderer();

	//SpriteRenderer();
	SpriteRenderer(TextureTag textureTag);
	SpriteRenderer(TextureTag textureTag, Vector2u currentImage, Vector2u imageCount);

	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	/// <summary>
	/// Returns a Sprite
	/// </summary>
	/// <returns></returns>
	Sprite GetSprite();

	void FlipSprite();

	Texture GetTexture();

	bool GetIsSpriteSheet();
	bool isSpriteSheet = false;

	/// <summary>
	/// Sets the sprite's texture based on TextureTag.
	/// </summary>
	/// <param name="textureTag">Which texture from the Asset Class </param>
	//void SetSprite(TextureTag textureTag);

	void SetTextureRect(IntRect& textureRect);

	IntRect* TextureRect;

	Vector2u* currentImage;
	Vector2u* imageCount;

	bool* GetFlipped();


private:
	Sprite* sprite;
	Texture* texture;

	bool* flipped;
};
