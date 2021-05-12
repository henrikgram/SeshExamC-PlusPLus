#include "LightSource.h"

LightSource::LightSource(Vector2f position)
{
	this->position = position;

	vector<Ray>::iterator it;

	for (int i = 0; i < 360; i+= 10)
	{
		float radians = i * (PI / 180);
		rays[i] = new Ray(position, Vector2f(cos(radians),sin(radians)));
	}

	
}
