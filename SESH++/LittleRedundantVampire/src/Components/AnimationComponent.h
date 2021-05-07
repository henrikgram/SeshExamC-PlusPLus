#pragma once
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
	/// <summary>
	/// Constructor til Animation.
	/// </summary>
	/// <param name="texture">Den texture (sprite sheet) som skal animeres.</param>
	/// <param name="imageCount">Hvor mange billeder der skal cycles imellem (raekker og kolonner).</param>
	/// <param name="switchTime">Hvor lang tid der skal g� imellem hvert skift af image.</param>
	AnimationComponent(SpriteRenderer* spriteRenderer, Vector2u imageCount, float switchTime, int row);

	/// <summary>
	/// Destructor til Animation.
	/// </summary>
	~AnimationComponent();

	//
	//row = d
	//deltaTime = d

	/// <summary>
	/// Update skal k�re hvert gameloop. Her k�rer animations-logikken.
	/// </summary>
	/// <param name="row">Den raekke i dit sprite sheet som skal cycles igennem.</param>
	/// <param name="deltaTime">Den tid der er g�et siden sidste Update.</param>
	/// <param name="faceRight">Om spilleren vender mod h�jre.</param>
	/// <param name="moving">Om spilleren st�r stille.</param>
	//void Update(float deltaTime, bool faceRight, bool moving);


	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

public:
	//Rectangle for vores texture.
	IntRect* TextureRect;

private:
	//Hvor mange billeder der skal cycles igennem.
	Vector2u imageCount;
	//Hvad er det nuvaerende billede i animationen.
	Vector2u currentImage;

	//Hvor hurtigt der skal cycles igennem animationen.
	float totalTime;
	//Hvor lang tid det skal tage at skifte billede.
	float switchTime;

	int row;

	SpriteRenderer* spriteRenderer;


};
