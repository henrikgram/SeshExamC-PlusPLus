#pragma once
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

//Guide til textures.
//https://www.youtube.com/watch?v=jJYHVQbZIfw&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=8

//Guide til sprite sheets.
//https://www.youtube.com/watch?v=-mcnW_6QpYA&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=9

//Guide til at animere ift. bevaegelse.
//https://www.youtube.com/watch?v=kAZVbPF6N4Q&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=11


class Attack
{
public:
	/// <summary>
	/// Constructor til Attack.
	/// </summary>
	/// <param name="texture">Din sprite</param>
	/// <param name="spawnPosition">Hvor angrebet skal spawne.</param>
	/// <param name="attackTime">Hvor laenge angrebet skal vaere på skaermen.</param>
	Attack(string textureName);

	/// <summary>
	/// Destructor til Attack.
	/// </summary>
	~Attack();

	/// <summary>
	/// Sørger for at opdatere Attack-logik.
	/// </summary>
	/// <param name="deltaTime">Tid der er gået siden sidste reset af time.</param>
	void Update(float deltaTime);

	/// <summary>
	/// Tegner Attack sprite.
	/// </summary>
	/// <param name="window">Det vindue som vi skal render sprite i.</param>
	void Draw(RenderWindow& window);

	RectangleShape GetBody() { return body; }

	void SetPosition(Vector2f position) { body.setPosition(position); }

	void SetRow(unsigned int row) { this->row = row; }
	void SetColumn(unsigned int column) { this->column = column; }


private:
	//Attacks rectangle.
	RectangleShape body;

	Texture texture;

	IntRect textureRect;

	unsigned int row;
	unsigned int column;

	//Om Attack vender mod højre.
	bool faceRight;
	//Om Attack vender mod højre.
	bool faceUp;
};
