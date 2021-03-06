#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "LightSource.h"
#include "Ray.h"


/// <summary>
/// Lightsource where all rays cast 360 degrees from a single point
/// </summary>
class PointLight : public LightSource
{
public:
	/// <summary>
	/// Lightsource where all rays cast 360 degrees from a single point
	/// </summary>
	/// <param name="position">The point where the rays will be casted from</param>
	/// <param name="walls">Which walls that it has to check for intersection</param>
	/// <param name="stepSize">bigger = less rays. If 1, then one ray pr. degree.</param>
	PointLight(Vector2f position, vector<VertexArray*>* walls, int stepSize = 5);

	/// <summary>
	/// Returns lines from the positon of the light to the intersecting points.
	/// Used for debug
	/// </summary>
	/// <returns></returns>
	vector<VertexArray> GetRayLines() override;

	 /*<summary>
	 Constructs a lightcone out of triangles based on the intersectinng points, from the look function. 
	 </summary>
	 <returns></returns>*/
	vector<VertexArray> GetLightCone() override;

	/// <summary>
	/// Moves the lightsource to a position
	/// </summary>
	/// <param name="position"></param>
	void Move(Vector2f position) override;
};

#endif