#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "OldAttack.h"
#include <string>

using namespace sf;
using namespace std;

//Guide til textures.
//https://www.youtube.com/watch?v=jJYHVQbZIfw&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=8

//Guide til sprite sheets.
//https://www.youtube.com/watch?v=-mcnW_6QpYA&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=9

//Guide til at animere ift. bevaegelse.
//https://www.youtube.com/watch?v=kAZVbPF6N4Q&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=11


class OldPlayer
{
public:
	/// <summary>
	/// Constructor til Player
	/// </summary>
	/// <param name="texture">Dit sprite sheet</param>
	/// <param name="imageCount">Hvor mange sprites dit sheet har (raekker og kolonner)</param>
	/// <param name="switchTime">Hvor hurtigt din animation skal cycle gennem sprites</param>
	/// <param name="speed">Hvor hurtigt Player bevaeger sig</param>
	OldPlayer(Texture* texture, Vector2u imageCount, float switchTime, float speed);

	/// <summary>
	/// Destructor til Player
	/// </summary>
	~OldPlayer();

	/// <summary>
	/// Soerger for at opdatere Player-logik, f.eks. movement.
	/// </summary>
	/// <param name="deltaTime">Tid der er gaaet siden sidste reset af time.</param>
	void Update(float deltaTime);

	/// <summary>
	/// Tegner spillerens sprite.
	/// </summary>
	/// <param name="window">Det vindue som vi skal render sprite i.</param>
	void Draw(RenderWindow& window);

	void Normalize(Vector2f& movement);

	Vector2f GetPosition() { return body.getPosition(); }

	//Collider GetCollider() { return Collider(body); }

private:
	//Spillerns rectangle
	RectangleShape body;

	//Spillerens animation-instans.
	Animation animation;

	OldAttack attack;

	//Hvilken raekke i spritesheet der skal animeres.
	unsigned int row;

	float attackTimer;
	float attackLength;

	//Spillerens bevaegelseshastighed.
	float speed;

	//Om spilleren vender mod hoejre.
	bool faceRight;
	//Om spilleren vender mod op.
	bool faceUp;
	//Om spilleren staar stille.
	bool moving;

	bool drawAttack;

	bool canMove;

	Keyboard::Key currentKey;
	Keyboard::Key previousKey;
};



