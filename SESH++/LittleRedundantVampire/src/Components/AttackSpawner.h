#ifndef ATTACKSPAWNER_H
#define ATTACKSPAWNER_H

#include "Attack.h"
#include "../Components/AnimationController.h"


/// <summary>
/// Component: Allows objects to spawn attacks, like the player.
/// </summary>
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

	/// <summary>
	/// Spawns an attack-object.
	/// </summary>
	/// <param name="textureTag">The texture of the attack.</param>
	/// <param name="objectTag">Whether it's player og enemy attack.</param>
	void CreateAttack(TextureTag textureTag, ObjectTag objectTag);

private:
	ObjectTag objectTag;

	float attackCooldown;
	float attackTimer;

	bool canAttack;
};

#endif