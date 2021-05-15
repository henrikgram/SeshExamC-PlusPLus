#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ray.h"
#include <math.h>

//Prededefined definition of pi for maths. 
#define PI 3.14159265

using namespace sf;

/// <summary>
/// Object which will beam out a number of Rays. 
/// </summary>
class LightSource
{
public:
	/// <summary>
	///  pointlight, an Object which will beam out a number of Rays in every direction. 
	/// </summary>
	/// <param name="position"></param>
	/// <param name="stepSize">The amount of rays. 1 is one ray pr. degree.</param>
	LightSource(Vector2f position, int stepSize = 5);

	/// <summary>
	/// Directional light, an Object which will beam out a number of rays in one direction on a given distance. 
	/// </summary>
	/// <param name="startPosition">Where the directional light should start</param>
	/// <param name="endPosition">Where it should end</param>
	LightSource(Vector2f startPosition, Vector2f endPosition, int angle ,int stepSize = 5);

	~LightSource();

	/// <summary>
	/// Cast out the rays, and check for intersection with the given objects
	/// </summary>
	/// <param name="walls">The object to check for interseciton with</param>
	/// <returns></returns>
	vector<Vector2f> Look(vector<VertexArray>* walls);

	/// <summary>
	/// Moves the lightsource to a position
	/// </summary>
	/// <param name="position"></param>
	void Move(Vector2f position);

	/// <summary>
	/// Cast out rays and only check for collision with one object. 
	/// </summary>
	/// <param name="object"></param>
	void LookAtSingleObject(VertexArray& object);

	/// <summary>
	/// Constructs a lightcone out of triangles based on the intersectinng points, from the look function. 
	/// </summary>
	/// <returns></returns>
	vector<VertexArray> GetLightCone();

	/// <summary>
	/// Returns lines from the positon of the light to the intersecting points.
	/// Used for debug
	/// </summary>
	/// <returns></returns>
	vector<VertexArray> GetRayLines();

	/// <summary>
	/// Uses pythagora to calcute the distance between to points. 
	/// </summary>
	/// <param name="pos1"></param>
	/// <param name="pos2"></param>
	/// <returns></returns>
	float GetDistance(Vector2f pos1, Vector2f pos2);

	/// <summary>
	/// Returns all the rays in the class.
	/// </summary>
	/// <returns></returns>
	vector<Ray*>* GetRays();
	Vector2f GetPosition();


private:
	Vector2f position;
	Vector2f endPosition;

	vector<Vector2f>* intersectingPoints = new vector<Vector2f>;
	vector<Ray*>* rays = new vector<Ray*>;
};

