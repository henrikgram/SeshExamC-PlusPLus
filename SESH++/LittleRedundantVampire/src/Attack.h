#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

//Guide til textures.
//https://www.youtube.com/watch?v=jJYHVQbZIfw&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=8

//Guide til sprite sheets.
//https://www.youtube.com/watch?v=-mcnW_6QpYA&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=9

//Guide til at animere ift. bev�gelse.
//https://www.youtube.com/watch?v=kAZVbPF6N4Q&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=11


class Attack
{
public:
	/// <summary>
	/// Constructor til Attack.
	/// </summary>
	/// <param name="texture">Din sprite</param>
	/// <param name="spawnPosition">Hvor angrebet skal spawne.</param>
	/// <param name="attackTime">Hvor l�nge angrebet skal v�re p� sk�rmen.</param>
	Attack(Texture* texture, Vector2f spawnPosition, float attackTime);

	/// <summary>
	/// Destructor til Attack.
	/// </summary>
	~Attack();

	/// <summary>
	/// S�rger for at opdatere Attack-logik.
	/// </summary>
	/// <param name="deltaTime">Tid der er g�et siden sidste reset af time.</param>
	void Update(float deltaTime);

	/// <summary>
	/// Tegner Attack sprite.
	/// </summary>
	/// <param name="window">Det vindue som vi skal render sprite i.</param>
	void Draw(RenderWindow& window);


private:
	//Attacks rectangle.
	RectangleShape body;

	//Om Attack vender mod h�jre.
	bool faceRight;
	//Om Attack vender mod h�jre.
	bool faceUp;
};


