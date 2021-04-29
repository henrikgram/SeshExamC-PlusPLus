#pragma once
#include "../Component.h"
#include "../../Enum/TextureTag.h"
#include "../Asset.h"
using namespace sf;

class SpriteRenderer : public Component
{
public:

	~SpriteRenderer();
	
	 void Awake() override;
	 void Start() override;
	 void Update() override;
	 void Destroy() override;
	 ComponentTag ToEnum() override;

	 /// <summary>
	 /// Returns a Sprite
	 /// </summary>
	 /// <returns></returns>
	 Sprite GetSprite();

	 /// <summary>
	 /// Sets the sprite's texture based on TextureTag.
	 /// </summary>
	 /// <param name="textureTag">Which texture from the Asset Class </param>
	 void SetSprite(TextureTag textureTag);

private:
	Sprite* sprite = new Sprite;
	Texture* texture = new Texture;
};

