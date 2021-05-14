#pragma once
#include "../Component.h"
#include "../Enum/TextureTag.h"
#include "../Asset.h"
#include "../Enum/ObjectTag.h"
#include <string>
using namespace sf;

class Attack : public Component
{
public:
	Attack(ObjectTag objectTag, Vector2f callerPosition, char direction, float attackLength);
	~Attack();

	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;


private:
	float attackTimer;
	float attackLength;

	Vector2f callerPosition;

	ObjectTag objectTag;

	char direction;
};

