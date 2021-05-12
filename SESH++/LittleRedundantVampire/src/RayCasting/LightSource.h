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

private:
	Vector2f position;
	vector<Ray*> rays;
};

