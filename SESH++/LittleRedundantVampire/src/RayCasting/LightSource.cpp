#include "LightSource.h"

LightSource::LightSource(Vector2f position)
{
	this->position = position;

	vector<Ray>::iterator it;

	for (int angle = 0; angle < 360; angle+= 10)
	{
		float radians = angle * (PI / 180);
		rays->push_back(new Ray(position, Vector2f(cos(radians)*40, sin(radians)*40)));

	}

	
}

vector<Ray*>* LightSource::GetRays()
{
	return rays;
}

Vector2f LightSource::GetPosition()
{
	return position;
}

void LightSource::Move(Vector2f position)
{
	this->position = position;
}

void LightSource::LookAtSingleWall(VertexArray& wall)
{
	vector<Ray*>::iterator it;

	for (it = rays->begin(); it < rays->end(); it++)
	{
		(*it)->Cast(wall);
	}
}

vector<Vector2f> LightSource::Look(vector<VertexArray>* walls)
{
	vector<Ray*>::iterator rayIt;
	vector<VertexArray>::iterator wallIt;

	vector<Vector2f> closestPoint;

	for (rayIt = rays->begin(); rayIt < rays->end(); rayIt++)
	{
		//TODO: ekstrem hotfix
		Vector2f closest;

		for (wallIt = walls->begin(); wallIt < walls->end(); wallIt++)
		{
			if ((*rayIt)->Cast((*wallIt)))
			{
				
				float newDistance = GetDistance(position, *(*rayIt)->GetIntersectionPoint());

				if (GetDistance(position,closest) > newDistance)
				{
					closest = *(*rayIt)->GetIntersectionPoint();
				}
			}
			
		}

		if (closest.x != 0 && closest.y !=0)
		{

			closestPoint.push_back(closest);
		}


	}

	return closestPoint;
}

float LightSource::GetDistance(Vector2f pos1, Vector2f pos2)
{
	return sqrt(pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2));
}


