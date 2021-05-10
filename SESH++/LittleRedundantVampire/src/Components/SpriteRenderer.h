#pragma once
#include "../Component.h"
#include "../Enum/TextureTag.h"
#include "../Asset.h"
using namespace sf;

class SpriteRenderer : public Component
{
public:

	~SpriteRenderer();

	SpriteRenderer();
	SpriteRenderer(Vector2u currentImage, Vector2u imageCount);


	
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
	 void SetSprite(TextureTag textureTag);

	 void SetTextureRect(IntRect& textureRect);

	 IntRect* TextureRect = new IntRect;

	 Vector2u* currentImage = new Vector2u;
	 Vector2u* imageCount = new Vector2u;


private:
	Sprite* sprite = new Sprite;
	Texture* texture = new Texture;

};

