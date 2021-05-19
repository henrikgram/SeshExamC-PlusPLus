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
	Attack(ObjectTag objectTag, float attackLength);
	~Attack();

	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;


private:

	float attackTimer;
	float attackLength;

	ObjectTag objectTag;
};

