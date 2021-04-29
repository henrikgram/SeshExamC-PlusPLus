#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

//Guide til animation af sprite sheet.
//https://www.youtube.com/watch?v=Aa8bXSq5LDE&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=10

//Guide til at animere ift. bevaegelse.
//https://www.youtube.com/watch?v=kAZVbPF6N4Q&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=11


class Animation
{
public:
	/// <summary>
	/// Constructor til Animation.
	/// </summary>
	/// <param name="texture">Den texture (sprite sheet) som skal animeres.</param>
	/// <param name="imageCount">Hvor mange billeder der skal cycles imellem (raekker og kolonner).</param>
	/// <param name="switchTime">Hvor lang tid der skal gå imellem hvert skift af image.</param>
	Animation(Texture* texture, Vector2u imageCount, float switchTime);

	/// <summary>
	/// Destructor til Animation.
	/// </summary>
	~Animation();

	//
	//row = d
	//deltaTime = d

	/// <summary>
	/// Update skal køre hvert gameloop. Her kører animations-logikken.
	/// </summary>
	/// <param name="row">Den raekke i dit sprite sheet som skal cycles igennem.</param>
	/// <param name="deltaTime">Den tid der er gået siden sidste Update.</param>
	/// <param name="faceRight">Om spilleren vender mod højre.</param>
	/// <param name="moving">Om spilleren står stille.</param>
	void Update(int row, float deltaTime, bool faceRight, bool moving);

public:
	//Rectangle for vores texture.
	IntRect TextureRect;

private:
	//Hvor mange billeder der skal cycles igennem.
	Vector2u imageCount;
	//Hvad er det nuvaerende billede i animationen.
	Vector2u currentImage;

	//Hvor hurtigt der skal cycles igennem animationen.
	float totalTime;
	//Hvor lang tid det skal tage at skifte billede.
	float switchTime;
};


