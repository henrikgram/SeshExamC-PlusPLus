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

	void CreateAttack(string direction);

private:
	ObjectTag* objectTag;

	float* attackLength;
	float* attackTimer;

	bool* canAttack;
};

