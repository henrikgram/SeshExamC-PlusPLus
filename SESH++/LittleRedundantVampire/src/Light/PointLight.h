#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "LightSource.h"
#include "Ray.h"


/// <summary>
/// TODO: add summary
/// </summary>
class PointLight : public LightSource
{
public:
	PointLight(Vector2f position, vector<VertexArray*>* walls, int stepSize = 5);

	/// <summary>
	/// Returns lines from the positon of the light to the intersecting points.
	/// Used for debug
	/// TODO: const
	/// </summary>
	/// <returns></returns>
	vector<VertexArray> GetRayLines() override;

	 /*<summary>
	 Constructs a lightcone out of triangles based on the intersectinng points, from the look function. 
	 //TODO: const
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