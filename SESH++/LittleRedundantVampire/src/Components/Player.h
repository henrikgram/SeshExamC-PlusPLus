#ifndef PLAYER_H
#define PLAYER_H

#include "../Component.h"
#include "../Enum/TextureTag.h"
#include "../Asset.h"
#include "AttackSpawner.h"
#include <string>
#include "../Observer/IGameEvent.h"
#include "SpriteRenderer.h"
#include "../Enum/ObjectTag.h"

using namespace sf;

/// <summary>
/// Component: The player character.
/// </summary>
class Player : public Component
{
public:
	Player();
	~Player();

	// Inherited via Component
	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void OnNotifyCollision(ObjectTag otherTag, string side) override;

private:
	GameObject* healthBar;
	SpriteRenderer* srHealthBar;

	int* health;
	float invincibilityTimer;
	bool invincible;
	bool damageTaken;
};

#endif