#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <SFML\Graphics.hpp>
#include "SpriteRenderer.h"

using namespace sf;


//Guide for animating using sprite sheet.
//https://www.youtube.com/watch?v=Aa8bXSq5LDE&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=10

//Guide for animating according to movement
//https://www.youtube.com/watch?v=kAZVbPF6N4Q&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=11


/// <summary>
/// Component: Handles animation.
/// </summary>
class AnimationComponent : public Component
{
public:
	/// <summary>
	/// Components that will animate by changing sprite through a spriteSheet
	/// </summary>
	/// <param name="spriteRenderer">Reference for the objects spriteRenderer</param>
	/// <param name="imageCount">How many rows of images, and how many images there is in one row</param>
	/// <param name="switchTime">How fast it should switch between frames</param>
	/// <param name="row">Default row to start the animation</param>
	AnimationComponent(SpriteRenderer* spriteRenderer, Vector2u imageCount, float switchTime, int row);
	~AnimationComponent();

	//Inherited from Component
	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	void OnNotify(string eventName, IListener* sender) override;

private:
	//How many pictures there are in the sheet.
	Vector2u imageCount;
	//The current image to draw.
	Vector2u currentImage;
	//The rectangle for the texture.
	IntRect textureRect;
	//How fast it should cycle through the animation.
	float totalTime;
	//Time between frames
	float switchTime;
	//Which row to animate currently.
	int row;

	SpriteRenderer* spriteRenderer;
};

#endif