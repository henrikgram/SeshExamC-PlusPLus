#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ray.h"
#include <math.h>

#define PI 3.14159265

using namespace sf;

class LightSource
{
public:
	LightSource(Vector2f position);
	vector<Ray*>* GetRays();
	Vector2f GetPosition();
	void Move(Vector2f position);

	void LookAtSingleWall(VertexArray& wall);

	vector<Vector2f> Look(vector<VertexArray> *walls);

	float GetDistance(Vector2f pos1, Vector2f pos2);


private:
	Vector2f position;
	vector<Ray*>* rays = new vector<Ray*>;
};

