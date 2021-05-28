#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector2f startPosition, Vector2f endPosition, vector<VertexArray*>* walls, int angle, int stepSize) : LightSource(startPosition, walls, stepSize)
{
	this->position = startPosition;
	this->endPosition = endPosition;
	this->angle = angle;

	bool horisontal;

	//If the y positions is the same, then the line is horisontal
	if (startPosition.y == endPosition.y)
	{
		horisontal = true;
	}
	else
	{
		horisontal = false;
	}

	float length = GetDistance(startPosition, endPosition);

	//TODO:* The angle is not relative to the line where the light emmits. So its counterintutitive to adjust the angle.
	//Calculates the angle to raidans.
	float radians = angle * (PI / 180);

	Vector2f vectorAngle = Vector2f(cos(radians), sin(radians));

	for (int i = 0; i < length; i += stepSize)
	{
		//For now only vertical or horisontal is allowed
		if (horisontal)
		{
			//offsets the position of the rays origin, so its evenly distributed on the line
			rays->push_back(new Ray(Vector2f(position.x + i, position.y), vectorAngle));
		}
		else
		{
			rays->push_back(new Ray(Vector2f(position.x, position.y + i), vectorAngle));
		}
	}
}

vector<VertexArray> DirectionalLight::GetRayLines()
{
	vector<Ray*>::iterator it;
	vector<VertexArray> RayLines;

	for (it = rays->begin(); it < rays->end(); it++)
	{
		VertexArray tmp = VertexArray(sf::LinesStrip, 2);
		tmp[0].color = Color::Yellow;
		tmp[1].color = Color::Yellow;
		tmp[0].position = (*it)->GetPosition();
		tmp[1].position = (*it)->GetIntersectionPoint();
		RayLines.push_back(tmp);
	}

	return RayLines;
}

vector<VertexArray> DirectionalLight::GetLightCone()
{
	vector<Ray*>::iterator it;

	vector<VertexArray> lightCone;

	Color coneColor = Color(255, 255, 0, 150);

	//Goes through all the intersecting points
	for (it = intersectingRays.begin(); it < intersectingRays.end(); it++)
	{
		VertexArray quad(Quads, 4);
		//One side of the quad is the current rays origin point, and a line to the intersecting point.
		quad[0].position = (*it)->GetPosition();
		quad[0].color = coneColor;

		//and then it connects to the first intersecting point
		quad[1].position = (*it)->GetIntersectionPoint();
		quad[1].color = coneColor;

		int index = (it - intersectingRays.begin());

		auto nxIt = std::next(it, 1);

		//and the next intersecting points, if it hasn't reached the end yet.
		if ((index + 1) != intersectingRays.size())
		{
			//If it isn't the last. The line connects to the next ray in the vector, and then back to the rays origin point.
			//and thus making a square
			quad[3].position = (*nxIt)->GetPosition();
			quad[3].color = coneColor;

			quad[2].position = (*nxIt)->GetIntersectionPoint();
			quad[2].color = coneColor;
		}
		else
		{
			break;
		}

		lightCone.push_back(quad);

	}

	return lightCone;
}

//TODO:* Dosen't work yet for directional light.
void DirectionalLight::Move(Vector2f position)
{
	int newXDif = this->position.x - position.x;
	int newYDif = this->position.y - position.y;

	this->position = position;
	this->endPosition = Vector2f(position.x + newXDif, position.y + newYDif);

	int length = GetDistance(position, endPosition);
	float offsetAmount = length / rays->size();
	vector<Ray*>::iterator it;

	for (it = rays->begin(); it < rays->end(); it++)
	{
		int index = it - rays->begin();
		Vector2f newPos = Vector2f(position.x, position.y + (index * offsetAmount));
		(*it)->Move(newPos);
	}
}
