#pragma once
#include "../Component.h"
#include "../Enum/TextureTag.h"
#include "../Asset.h"
#include "AttackSpawner.h"
#include <string>
#include "../Observer/IGameEvent.h"

using namespace sf;

class Player : public Component
{
public:
	Player();
	~Player();

	void Move(Vector2f velocity);

	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void OnNotifyCollision(ObjectTag otherTag, string side) override;

	void Normalize();
	void UpdateAnimation();
	IGameEvent ChangeAnimation;


private:
	bool flipped = false;
	float speed;

	Vector2f velocity;
};
