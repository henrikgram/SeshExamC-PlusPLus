#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "LightSource.h"
#include "Ray.h"


/// <summary>
/// TODO: Add summary.
/// </summary>
class DirectionalLight : public LightSource
{
public:
	DirectionalLight(Vector2f startPosition, Vector2f endPosition, vector<VertexArray*>* walls, int angle = 0, int stepSize = 5);

	/// <summary>
	/// Returns lines from the positon of the light to the intersecting points.
	/// Used for debugging.
	/// TODO:const
	/// </summary>
	/// <returns></returns>
	vector<VertexArray> GetRayLines() override;
	/// <summary>
	/// Constructs a lightcone out of triangles based on the intersectinng points, from the look function. 
	/// TODO: const
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