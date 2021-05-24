#ifndef ATTACK_H
#define ATTACK_H

#include "../Component.h"
#include "../Enum/TextureTag.h"
#include "../Asset.h"
#include "../Enum/ObjectTag.h"
#include <string>

using namespace sf;


/// <summary>
/// Component: The object that is created when a player or enemy attacks.
/// </summary>
class Attack : public Component
{
public:
	Attack(ObjectTag objectTag, float attackLength);
	~Attack();

	// Inherited via Component
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

#endif