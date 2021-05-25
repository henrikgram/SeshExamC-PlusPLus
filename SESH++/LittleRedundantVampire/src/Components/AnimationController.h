#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <string>
#include "../Observer/IGameEvent.h"
#include "SpriteRenderer.h"

using namespace std;


/// <summary>
/// Component: Handles which type of animation to run. For movement or others.
/// </summary>
class AnimationController : public Component
{
public:
	/// <summary>
	/// For animating moving objects such as Player.
	/// </summary>
	/// <param name="spriteRenderer">SpriteRenderer for the object to animate.</param>
	/// <param name="noAniRow">Default animation row.</param>
	/// <param name="upAniRow">Up animation row.</param>
	/// <param name="downAniRow">Down animation row.</param>
	/// <param name="leftAniRow">Left animation row.</param>
	/// <param name="rightAniRow">Right animation row.</param>
	AnimationController(SpriteRenderer& spriteRenderer, string noAniRow, string upAniRow, string downAniRow, string leftAniRow, string rightAniRow);

	/// <summary>
	/// For health bar animation, or other animation where the row is decrementing.
	/// </summary>
	/// <param name="spriteRenderer">SpriteRenderer for the object to animate.</param>
	/// <param name="currentRow">The current row to animate.</param>
	/// <param name="firstRow">The first row to animate.</param>
	AnimationController(SpriteRenderer& spriteRenderer, int* currentRow, int firstRow);

	~AnimationController();

	// Inherited via Component
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update(Time* timePerFrame) override;
	virtual void Destroy() override;
	virtual ComponentTag ToEnum() override;
	
	void AttachListenerToChangeAnimation(IListener* listener);

private:
	/// <summary>
	/// For animating objects that move in four directions, like the Player.
	/// </summary>
	void MovementAnimation();
	/// <summary>
	/// For running a very simple animation that doesn't change much.
	/// </summary>
	void DecrementingRowAnimation();


private:
	IGameEvent changeAnimation;

	SpriteRenderer& spriteRenderer;

	string noAniRow;
	string upAniRow;
	string downAniRow;
	string leftAniRow;
	string rightAniRow;

	bool movementAnimation;
	bool decrementAnimation;

	//Previous animated row.
	int previousRow;
	//Current row to animate.
	int* currentRow;
	//First row to animate.
	int firstRow;
};

#endif