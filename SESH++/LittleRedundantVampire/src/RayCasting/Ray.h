#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Ray
{
public:
	Ray(Vector2f position, Vector2f direction);
	Ray();
	bool Cast(VertexArray& wall);
	void LookAt(Vector2f);
	VertexArray* GetVertexArray();
	Vector2f* GetIntersectionPoint();

private:
	VertexArray* ray = new VertexArray(sf::LinesStrip,2);
	Vector2f* intersection = new Vector2f;
};

