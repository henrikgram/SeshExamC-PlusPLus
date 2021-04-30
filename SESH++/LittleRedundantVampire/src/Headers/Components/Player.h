#pragma once
#include "../Component.h"
#include "../../Enum/TextureTag.h"
#include "../Asset.h"
#include "../Component.h"
using namespace sf;

class Player : public Component
{
public:
	~Player();

	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void Normalize(Vector2f& movement);


private:
	float speed;
};

