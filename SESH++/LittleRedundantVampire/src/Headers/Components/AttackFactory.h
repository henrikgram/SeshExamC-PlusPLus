#pragma once
#include "Attack.h"


class AttackFactory
{
public:
	AttackFactory();
	~AttackFactory();

	void CreateAttack(ObjectTag tag, Vector2f callerPosition, string direction);
};

