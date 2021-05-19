#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <SFML\Graphics.hpp>
#include "SpriteRenderer.h"

using namespace sf;


//Guide til animation af sprite sheet.
//https://www.youtube.com/watch?v=Aa8bXSq5LDE&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=10

//Guide til at animere ift. bevaegelse.
//https://www.youtube.com/watch?v=kAZVbPF6N4Q&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=11


class AnimationComponent : public Component
{
public:
	AnimationComponent(SpriteRenderer* spriteRenderer, Vector2u imageCount, float switchTime, int row);
	~AnimationComponent();

	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	void OnNotify(string eventName, IListener* sender) override;
	ComponentTag ToEnum() override;


private:
	//How many pictures there are in the sheet.
	Vector2u imageCount;
	//The current image to draw.
	Vector2u currentImage;

	//The rectangle for the texture.
	IntRect* textureRect;

	//How fast it should cycle through the animation.
	float totalTime;

	//Time between frames
	float switchTime;

	//Which row to animate currently.
	int row;

	SpriteRenderer* spriteRenderer;
};

#endif