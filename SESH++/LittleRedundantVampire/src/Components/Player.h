#pragma once
#include "../Component.h"
#include "../Enum/TextureTag.h"
#include "../Asset.h"
#include "AttackFactory.h"
#include <string>
#include "../Observer/IGameEvent.h"
#include "SpriteRenderer.h"

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

	void NotifyCollision(ObjectTag otherTag) override;

	IGameEvent ChangeAnimation;
	void Normalize();
	void UpdateAnimation();

private:
	float speed;
	bool flipped = false;
	Attack* attack;
	string direction;
	Vector2f velocity;
	SpriteRenderer* sr;


};
