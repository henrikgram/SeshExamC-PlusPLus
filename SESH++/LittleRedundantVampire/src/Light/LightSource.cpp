#include "LightSource.h"

LightSource::LightSource(Vector2f position, vector<VertexArray*>* walls, int stepSize)
{
	this->walls = walls;
	drawComponent = true;
}

LightSource::~LightSource()
{
	delete intersectingPoints;
	intersectingPoints = nullptr;

	vector<Ray*>::iterator it;

	for (it = rays->begin(); it < rays->end(); it++)
	{
		delete* it;
		*it = nullptr;
	}

	delete rays;
	rays = nullptr;
}

vector<Ray*>* LightSource::GetRays()
{
	return rays;
}

Vector2f LightSource::GetPosition()
{
	return position;
}

void LightSource::Awake()
{
}

void LightSource::Start()
{
}

void LightSource::Update(Time* timePerFrame)
{
	CastRays(walls);
}

void LightSource::Destroy()
{
	//TODO: kald destructor
	//LightSource::~LightSource();
}

ComponentTag LightSource::ToEnum()
{
	return ComponentTag::LIGHT;
}

void LightSource::Move(Vector2f position)
{
	this->position = position;
	vector<Ray*>::iterator it;

	for (it = rays->begin(); it < rays->end(); it++)
	{
		(*it)->Move(position);
	}
}

void LightSource::LookAtSingleObject(VertexArray& object)
{
	vector<Ray*>::iterator it;

	for (it = rays->begin(); it < rays->end(); it++)
	{
		(*it)->Cast(object);
	}
}

vector<Vector2f> LightSource::CastRays(vector<VertexArray*>* walls)
{
	intersectingRays->clear();

	vector<Ray*>::iterator rayIt;
	vector<VertexArray*>::iterator wallIt;

	//Array to store the closest intersection point. 
	vector<Vector2f> closestPoint;

	//Goes through every ray, and checks every wall to find the closest intersection. 
	for (rayIt = rays->begin(); rayIt < rays->end(); rayIt++)
	{
		//TODO: ekstrem hotfix
		//To save the contender for closest point. 
		Vector2f closest = Vector2f(10000, 10000);

		for (wallIt = walls->begin(); wallIt < walls->end(); wallIt++)
		{
			//If there is an interection 
			if ((*rayIt)->Cast(*(*wallIt)))
			{
				//Caclulate the distance to the new point
				float newDistance = GetDistance(position, (*rayIt)->GetIntersectionPoint());

				//If the distance to the new point is shorter than the distance to the closest
				if (GetDistance(position, closest) > newDistance)
				{
					//the closest will then be the new intersection point
					closest = (*rayIt)->GetIntersectionPoint();
				}
			}
		}

		// if it has actually found any intersection, add it to the closest intersection
		if (closest.x != 10000 && closest.y != 10000)
		{
			(*rayIt)->SetIntersection(closest);
			intersectingRays->push_back(*rayIt);
			closestPoint.push_back(closest);
		}
	}
	//Update the list with itersecting points
	intersectingPoints->clear();
	intersectingPoints->insert(intersectingPoints->begin(), closestPoint.begin(), closestPoint.end());

	return closestPoint;
}

float LightSource::GetDistance(Vector2f pos1, Vector2f pos2)
{
	return sqrt(pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2));
}