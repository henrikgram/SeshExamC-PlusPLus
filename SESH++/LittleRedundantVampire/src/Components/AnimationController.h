#pragma once
#include <string>
#include "../Observer/IGameEvent.h"
#include "../GameObject.h"
#include "SpriteRenderer.h"
#include "Movement.h"

using namespace std;


class AnimationController : public Component
{
public:
	/// <summary>
	/// For animating moving objects such as Player.
	/// </summary>
	AnimationController(SpriteRenderer& spriteRenderer, 
		string noAniRow, string upAniRow, string downAniRow, string leftAniRow, string rightAniRow);
	AnimationController(SpriteRenderer& spriteRenderer, int* currentRow, int firstRow);
	~AnimationController();


	// Inherited via Component
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update(Time* timePerFrame) override;
	virtual void Destroy() override;
	virtual ComponentTag ToEnum() override;

	IGameEvent ChangeAnimation;


private:
	void MovementAnimation();
	void DecrementingRowAnimation();

	SpriteRenderer& spriteRenderer;

	string noAniRow;
	string upAniRow;
	string downAniRow;
	string leftAniRow;
	string rightAniRow;

	bool movementAnimation;
	bool decrementAnimation;

	int previousRow;
	int* currentRow;
	int firstRow;
};

