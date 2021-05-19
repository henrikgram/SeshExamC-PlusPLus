#pragma once
#include "Attack.h"


class AttackSpawner : public Component
{
public:
	AttackSpawner(ObjectTag tag);
	~AttackSpawner();

	// Inherited via Component
	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void CreateAttack(TextureTag textureTag, ObjectTag objectTag);

private:
	ObjectTag objectTag;

	float attackCooldown;
	float attackTimer;

	bool canAttack;
};

