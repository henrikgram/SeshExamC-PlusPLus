#include "Light.h"

Light::Light(Vector2f direction)
{
	this->direction = direction;
	line = new VertexArray(sf::LinesStrip, 2);
}

void Light::Awake()
{
}

void Light::Start()
{
}

void Light::Update(Time* timePerFrame)
{
}

void Light::Destroy()
{
}

void Light::CastRay()
{
	//(*line)[0].position.x = 500;
	/*line[0]->position.y = 500;

	line[1]->position.x = 800;
	line[1]->position.y = 800;
	*/
	
	(*line)[0].position.x = gameObject->position->x;
	(*line)[0].position.y = gameObject->position->y;

	(*line)[1].position.x = gameObject->position->x + direction.x * 1000;
	(*line)[1].position.y = gameObject->position->y + direction.y * 1000;;


	//line->color = sf::Color::Red;


}

VertexArray* Light::GetRays()
{
	CastRay();
	return line;
}



ComponentTag Light::ToEnum()
{
	return ComponentTag::LIGHT;
}
