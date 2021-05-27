#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "LightSource.h"
#include "Ray.h"


/// <summary>
/// Lightsource where all lightrays points in one direction from mulitple points on a line.
/// </summary>
class DirectionalLight : public LightSource
{
public:
	/// <summary>
	/// Lightsource where all lightrays points in one direction from mulitple points on a line.
	/// </summary>
	/// <param name="startPosition">Where the line, which the rays is casted from starts</param>
	/// <param name="endPosition">Where the line, which the rays is casted from ends. Make sure the line is either perfectly horisontal or vertical, because of missing functionality regarding skewed lightsource</param>
	/// <param name="walls">Which walls that it has to check for intersection</param>
	/// <param name="angle">The angle that the rays will cast</param>
	/// <param name="stepSize">Bigger = less rays</param>
	DirectionalLight(Vector2f startPosition, Vector2f endPosition, vector<VertexArray*>* walls, int angle = 0, int stepSize = 5);

	/// <summary>
	/// Returns lines from the positon of the light to the intersecting points.
	/// Used for debugging.
	/// </summary>
	/// <returns></returns>
	vector<VertexArray> GetRayLines() override;
	/// <summary>
	/// Constructs a lightcone out of triangles based on the intersectinng points, from the look function. 
	/// </summary>
	/// <returns></returns>
	vector<VertexArray> GetLightCone() override;
	/// <summary>
	/// Moves the lightsource to a position.
	/// </summary>
	/// <param name="position"></param>
	void Move(Vector2f position) override;

private:
	Vector2f endPosition;
	int angle;
};

#endif