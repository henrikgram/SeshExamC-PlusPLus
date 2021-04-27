#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
using namespace sf;

//Guide til textures.
//https://www.youtube.com/watch?v=jJYHVQbZIfw&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=8

//Guide til sprite sheets.
//https://www.youtube.com/watch?v=-mcnW_6QpYA&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=9

//Guide til at animere ift. bev�gelse.
//https://www.youtube.com/watch?v=kAZVbPF6N4Q&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=11


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

	/// <summary>
	/// Destructor til Player
	/// </summary>
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

	Vector2f GetPosition() { return body.getPosition(); }

	Collider GetCollider() { return Collider(body); }

private:
	//Spillerns rectangle
	RectangleShape body;

	//Spillerens animation-instans.
	Animation animation;

	//Hvilken r�kke i spritesheet der skal animeres.
	unsigned int row;

	//Spillerens bev�gelseshastighed.
	float speed;

	//Om spilleren vender mod h�jre.
	bool faceRight;
	//Om spilleren vender mod op.
	bool faceUp;
	//Om spilleren st�r stille.
	bool moving;
};
