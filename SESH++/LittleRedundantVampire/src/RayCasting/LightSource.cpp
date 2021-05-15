#include "LightSource.h"

LightSource::LightSource(Vector2f position, int stepSize)
{
	this->position = position;

	vector<Ray>::iterator it;

	//makes a ray for every stepSize amount. If stepsize is 1 then its 1 ray pr degree. 
	//If 10 then its one ray every 10 degrees etc.
	for (int angle = 0; angle < 360; angle+= stepSize)
	{
		//Calculates the angle to raidans. 
		float radians = angle * (PI / 180);

		//Makes a new ray with the same start positon as the light, and converts radians to a vector. 
		rays->push_back(new Ray(position, Vector2f(cos(radians)*40, sin(radians)*40)));
	}
}

LightSource::LightSource(Vector2f startPosition, Vector2f endPosition,int angle, int stepSize)
{
	this->position = position;
	this->endPosition = endPosition;

	int length = GetDistance(position, endPosition);

	//Calculates the angle to raidans. 
	float radians = angle * (PI / 180);



	for (int i = 0; i < length; i+= stepSize)
	{
		rays->push_back(new Ray(position, Vector2f(cos(radians) * 40, sin(radians) * 40)));
	}

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


vector<Vector2f> LightSource::Look(vector<VertexArray>* walls)
{
	vector<Ray*>::iterator rayIt;
	vector<VertexArray>::iterator wallIt;

	//Array to store the closest intersection point. 
	vector<Vector2f> closestPoint;

	//Goes through every ray, and checks every wall to find the closes intersection. 
	for (rayIt = rays->begin(); rayIt < rays->end(); rayIt++)
	{
		//TODO: ekstrem hotfix
		//TO save the contender for closest point. 
		Vector2f closest = Vector2f(10000,10000);

		for (wallIt = walls->begin(); wallIt < walls->end(); wallIt++)
		{
			//If there is an interection 
			if ((*rayIt)->Cast((*wallIt)))
			{
				//Caclulate the distance to the new point
				float newDistance = GetDistance(position, *(*rayIt)->GetIntersectionPoint());

				//If the distance to the new point is shorter than the distance to the closest
				if (GetDistance(position,closest) > newDistance)
				{
					//the closest will then be the new intersection point
					closest = *(*rayIt)->GetIntersectionPoint();
				}
			}
			
		}

		// if it has actually found any intersection, add it to the closest intersection
		if (closest.x != 10000 && closest.y !=10000)
		{
			closestPoint.push_back(closest);
		}


	}
	//Update the list with itersecting points
	intersectingPoints->clear();
	intersectingPoints->insert(intersectingPoints->begin(), closestPoint.begin(), closestPoint.end());

	return closestPoint;
}

vector<VertexArray> LightSource::GetLightCone()
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

vector<VertexArray> LightSource::GetRayLines()
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

float LightSource::GetDistance(Vector2f pos1, Vector2f pos2)
{
	return sqrt(pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2));
}


