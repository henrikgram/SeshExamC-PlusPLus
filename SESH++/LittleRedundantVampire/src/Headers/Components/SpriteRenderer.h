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

	 Sprite GetSprite();
	 void SetSprite(TextureTag textureTag);

private:
	Sprite* sprite;
};

