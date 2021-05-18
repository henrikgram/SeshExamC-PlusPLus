#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector2f startPosition, Vector2f endPosition, int angle, int stepSize) : LightSource(startPosition, stepSize)
{
	this->position = startPosition;
	this->endPosition = endPosition;
	this->angle = angle;

	bool horisontal;

	if (startPosition.y == endPosition.y)
	{
		horisontal = true;
	}
	else
	{
		horisontal = false;
	}

	float length = GetDistance(startPosition, endPosition);

	//TODO: ikke den bedste sammenhæng med vinkler og retning, men kan fikses senere, virker nu. 
	//Calculates the angle to raidans. 
	float radians = angle * (PI / 180);

	Vector2f vectorAngle = Vector2f(cos(radians), sin(radians));

	for (int i = 0; i < length; i += stepSize)
	{
		if (horisontal)
		{
			rays->push_back(new Ray(Vector2f(position.x +i, position.y), vectorAngle));
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
		tmp[0].color = Color::Black;
		tmp[1].color = Color::Black;
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



	//Goes through all the intersecting points
	for (it = intersectingRays->begin(); it < intersectingRays->end(); it++)
	{

		VertexArray quad(Quads, 4);
		//every triangle starts at the lights position
		quad[0].position = (*it)->GetPosition();
		quad[0].color = Color::Yellow;


		//and then it connects to the first intersecting point
		quad[1].position = (*it)->GetIntersectionPoint();
		quad[1].color = Color::Yellow;

		int index = (it - intersectingRays->begin());

		auto nxIt = std::next(it, 1);

		//and the next intersecting points, if it havent reached the end yet. 
		if ((index + 1) != intersectingRays->size())
		{
			quad[3].position = (*nxIt)->GetPosition();
			quad[3].color = Color::Yellow;

			quad[2].position = (*nxIt)->GetIntersectionPoint();
			quad[2].color = Color::Yellow;
		}
		else
		{
			auto prvIt = std::prev(it, 1);
			//if it has reached the end, then just connect it to the first intersecting point. 
			quad[3].position = (*prvIt)->GetPosition();
			quad[3].color = Color::Yellow;

			quad[2].position = (*prvIt)->GetIntersectionPoint();
			quad[2].color = Color::Yellow;
		}

		lightCone.push_back(quad);

	

		

	
	}

	return lightCone;
}


//TODO: dosent work yet for directional light
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
