#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
using namespace sf;


class Player
{
public:
	/// <summary>
	/// Constructor til Player
	/// </summary>
	/// <param name="texture">Dit sprite sheet</param>
	/// <param name="imageCount">Hvor mange sprites dit sheet har (r�kker og kolonner)</param>
	/// <param name="switchTime">Hvor hurtigt din animation skal cycle gennem sprites</param>
	/// <param name="speed">Hvor hurtigt Player bev�ger sig</param>
	Player(Texture* texture, Vector2u imageCount, float switchTime, float speed);

	~Player();

	/// <summary>
	/// S�rger for at opdatere Player-logik, f.eks. movement.
	/// </summary>
	/// <param name="deltaTime">Tid der er g�et siden sidste reset af time.</param>
	void Update(float deltaTime);

	/// <summary>
	/// Tegner spillerens sprite.
	/// </summary>
	/// <param name="window">Det vindue som vi skal render sprite i.</param>
	void Draw(RenderWindow& window);

	void Normalize(Vector2f& movement);

private:
	//Spillerns rectangle
	RectangleShape body;
	//Spillerens animation-instans
	Animation animation;
	//Hvilken r�kke i spritesheet der skal animeres
	unsigned int row;
	//spillerens bev�gelseshastighed
	float speed;
	//om spilleren vender mod h�jre
	bool faceRight;
};

