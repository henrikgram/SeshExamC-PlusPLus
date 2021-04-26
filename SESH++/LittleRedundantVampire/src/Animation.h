#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

class Animation
{
public:
	//Constructor til Animation.
	//texture = den texture (sprite sheet) som skal animere3s.
	//imageCount = hvor mange billeder der skal cycles imellem (r�kker og kolonner).
	//switchTime = hvor lang tid der skal g� imellem hvert skift af image.
	Animation(Texture* texture, Vector2u imageCount, float switchTime);

	//Destructor til Animation.
	~Animation();

	//Update skal k�re hvert gameloop. Her k�rer animations-logikken.
	//row = den r�kke i dit sprite sheet som skal cycles igennem.
	//deltaTime = den tid der er g�et siden sidste Update.
	void Update(int row, float deltaTime, bool faceRight, bool moving);

public:
	//Rectangle for vores texture.
	IntRect textureRect;

private: 
	//Hvor mange billeder der skal cycles igennem.
	Vector2u imageCount;
	//Hvad er det nuv�rende billede i animationen.
	Vector2u currentImage;

	//Hvor hurtigt der skal cycles igennem animationen.
	float totalTime;
	//Hvor lang tid det skal tage at skifte billede.
	float switchTime;
};

