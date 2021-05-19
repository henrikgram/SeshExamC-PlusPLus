#pragma once
#include "../Component.h"
#include "../Enum/TextureTag.h"
#include "../Asset.h"
#include "AttackSpawner.h"
#include <string>
#include "../Observer/IGameEvent.h"
#include "SpriteRenderer.h"
#include "../Enum/ObjectTag.h"

using namespace sf;

class Player : public Component
{
public:
	Player();
	~Player();

	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void OnNotifyCollision(ObjectTag otherTag, string side) override;


private:

	int* health;

	GameObject* healthBar;
	SpriteRenderer* srHealthBar;

	//Delete later, only for testing.
	float timer;

	float invincibilityTimer;

	bool invincible;
	bool damageTaken;
};
