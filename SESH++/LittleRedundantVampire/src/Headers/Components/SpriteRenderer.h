#pragma once
#include "../Component.h"
#include "../../Enum/TextureTag.h"

class SpriteRenderer : public Component
{
public:

	~SpriteRenderer();
	
	 void Awake() override;
	 void Start() override;
	 void Update() override;
	 void Destroy() override;
	 Tag ToEnum() override;

	 Sprite GetSprite();
	 void SetSprite(TextureTag textureTag);

private:
	Sprite* sprite;
};

