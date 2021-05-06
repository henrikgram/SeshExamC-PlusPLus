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
	Attack(ObjectTag tag, Vector2f callerPosition, string direction);
	~Attack();

	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void CreateAttack();
	void StartAttack();


private:
	float attackTimer;
	float attackLength;

	string* direction;

	Vector2f* callerPosition;

	ObjectTag* tag;
};

