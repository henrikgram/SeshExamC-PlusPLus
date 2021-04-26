#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

class Animation
{
public:
	//Constructor til Animation.
	//texture = den texture (sprite sheet) som skal animere3s.
	//imageCount = hvor mange billeder der skal cycles imellem (rækker og kolonner).
	//switchTime = hvor lang tid der skal gå imellem hvert skift af image.
	Animation(Texture* texture, Vector2u imageCount, float switchTime);

	//Destructor til Animation.
	~Animation();

	//Update skal køre hvert gameloop. Her kører animations-logikken.
	//row = den række i dit sprite sheet som skal cycles igennem.
	//deltaTime = den tid der er gået siden sidste Update.
	void Update(int row, float deltaTime, bool faceRight, bool moving);

public:
	//Rectangle for vores texture.
	IntRect textureRect;

private: 
	//Hvor mange billeder der skal cycles igennem.
	Vector2u imageCount;
	//Hvad er det nuværende billede i animationen.
	Vector2u currentImage;

	//Hvor hurtigt der skal cycles igennem animationen.
	float totalTime;
	//Hvor lang tid det skal tage at skifte billede.
	float switchTime;
};

