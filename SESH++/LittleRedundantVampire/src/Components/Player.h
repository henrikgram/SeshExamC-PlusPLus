#pragma once
#include "../Component.h"
#include "../Enum/TextureTag.h"
#include "../Asset.h"
#include "AttackSpawner.h"
#include <string>

using namespace sf;

class Player : public Component
{
public:
	~Player();

	void Move(Vector2f velocity);

	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void NotifyCollision(ObjectTag otherTag) override;

	void Normalize();

private:
	float speed;

	string direction;

	Vector2f velocity;
};
