#pragma once
#include <SFML\Graphics.hpp>
#include "SpriteRenderer.h"
#include "AnimationController.h"
using namespace sf;

//Guide til animation af sprite sheet.
//https://www.youtube.com/watch?v=Aa8bXSq5LDE&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=10

//Guide til at animere ift. bevaegelse.
//https://www.youtube.com/watch?v=kAZVbPF6N4Q&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=11


class AnimationComponent : public Component
{
public:

	/// <summary>
	/// Components that will animate by changing sprite through a spriteSheet
	/// </summary>
	/// <param name="spriteRenderer">Reference for the objects spriteRenderer</param>
	/// <param name="imageCount">How many rows of images, and how many images that is in one row</param>
	/// <param name="switchTime">How fast it should switch between frames</param>
	/// <param name="row">Default row to start the animation</param>
	AnimationComponent(SpriteRenderer* spriteRenderer, Vector2u imageCount, float switchTime, int row);

	~AnimationComponent();

	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	void OnNotify(string eventName, IListener* sender) override;
	ComponentTag ToEnum() override;

public:


private:
	//How many pictures that is in one animation row
	Vector2u imageCount;
	IntRect* TextureRect;
	Vector2u currentImage;

	//How fast it should cycle through the animation.
	float totalTime;

	//Time between frames
	float switchTime;

	int row;

	SpriteRenderer* spriteRenderer;
};
