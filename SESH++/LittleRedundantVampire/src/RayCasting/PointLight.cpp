#include "PointLight.h"

PointLight::PointLight(Vector2f position, int stepSize) : LightSource(position, stepSize)
{
	this->position = position;

	vector<Ray>::iterator it;

	//makes a ray for every stepSize amount. If stepsize is 1 then its 1 ray pr degree. 
	//If 10 then its one ray every 10 degrees etc.
	for (int angle = 0; angle < 360; angle += stepSize)
	{
		//Calculates the angle to raidans. 
		float radians = angle * (PI / 180);

		//Makes a new ray with the same start positon as the light, and converts radians to a vector. 
		rays->push_back(new Ray(position, Vector2f(cos(radians) * 40, sin(radians) * 40)));
	}
}

vector<VertexArray> PointLight::GetRayLines()
{
	vector<Vector2f>::iterator it;
	vector<VertexArray> RayLines;

	for (it = intersectingPoints->begin(); it < intersectingPoints->end(); it++)
	{
		VertexArray tmp = VertexArray(sf::LinesStrip, 2);
		tmp[0].color = Color::Black;
		tmp[1].color = Color::Black;
		tmp[0].position = position;
		tmp[1].position = *it;
		RayLines.push_back(tmp);
	}

	return RayLines;
}

vector<VertexArray> PointLight::GetLightCone()
{
	vector<Vector2f>::iterator it;

	vector<VertexArray> lightCone;

	//Goes through all the intersecting points
	for (it = intersectingPoints->begin(); it < intersectingPoints->end(); it++)
	{

		VertexArray triangle(sf::Triangles, 3);
		//every triangle starts at the lights position
		triangle[0].position = position;
		triangle[0].color = Color::Yellow;


		//and then it connects to the first intersecting point
		triangle[1].position = *it;
		triangle[1].color = Color::Yellow;

		int index = (it - intersectingPoints->begin());

		//and the next intersecting points, if it havent reached the end yet. 
		if ((index + 1) != intersectingPoints->size())
		{
			triangle[2].position = *(it + 1);
			triangle[2].color = Color::Yellow;

		}
		else
		{
			//if it has reached the end, then just connect it to the first intersecting point. 
			triangle[2].position = *intersectingPoints->begin();
			triangle[2].color = Color::Yellow;
		}

		lightCone.push_back(triangle);
	}

	return lightCone;
}

void PointLight::Move(Vector2f position)
{
	this->position = position;
	vector<Ray*>::iterator it;

	for (it = rays->begin(); it < rays->end(); it++)
	{
		(*it)->Move(position);
	}
}
