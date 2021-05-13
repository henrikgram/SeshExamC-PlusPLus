#pragma once
#include <string>
#include "../Observer/IGameEvent.h"
#include "../GameObject.h"
#include "SpriteRenderer.h"
#include "Movement.h"

using namespace std;


class AnimationController : public IListener
{
public:
	/// <summary>
	/// For animating moving objects such as Player.
	/// </summary>
	AnimationController(Movement* movementComponent, SpriteRenderer* spriteRenderer, GameObject* gameObject, 
		string noAniRow, string upAniRow, string downAniRow, string leftAniRow, string rightAniRow);
	~AnimationController();

	void MovementAnimation();

	IGameEvent ChangeAnimation;


private:
	GameObject* gameObject;
	
	SpriteRenderer* spriteRenderer;

	Movement* movementComponent;

	string noAniRow;
	string upAniRow;
	string downAniRow;
	string leftAniRow;
	string rightAniRow;

	// Inherited via IListener
	virtual void OnNotify(std::string eventName, IListener* sender) override;
};

