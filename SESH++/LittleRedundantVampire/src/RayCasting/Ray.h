#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Ray
{
public:
	/// <summary>
	/// A line that gets shot out from a point, and then detects intersection with all lines that i collides with
	/// </summary>
	/// <param name="position">Start position</param>
	/// <param name="direction">Direction to fire the ray</param>
	Ray(Vector2f position, Vector2f direction);

	Ray();
	~Ray();

	/// <summary>
	/// Uses line-line intersection, to check if given two points on each line if they will intersect at some point.
	/// </summary>
	/// <param name="wall">The line it has to calculate if there is an intersection</param>
	/// <returns></returns>
	bool Cast(VertexArray& wall);

	/// <summary>
	/// Changes the direction of the ray
	/// </summary>
	/// <param name=""></param>
	void LookAt(Vector2f direction);

	/// <summary>
	/// Moves the ray to a position
	/// </summary>
	/// <param name="position"></param>
	void Move(Vector2f position);

	/// <summary>
	/// Returns the VertexArray
	/// </summary>
	/// <returns></returns>
	VertexArray* GetVertexArray();

	/// <summary>
	/// Returns the intersection point
	/// </summary>
	/// <returns></returns>
	Vector2f GetIntersectionPoint();

	Vector2f GetPosition();

	void SetIntersection(Vector2f position);

	
private:
	Vector2f position;
	Vector2f direction;
	VertexArray* ray = new VertexArray(sf::LinesStrip, 2);
	Vector2f intersection;// = new Vector2f;
};

