#pragma once
#include "../Component.h"
using namespace sf;

class Light : public Component
{
public:

	Light(Vector2f direction);
	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;

	void CastRay();
	VertexArray* GetRays();

	ComponentTag ToEnum() override;

private:
	VertexArray* line;// = new VertexArray(sf::LinesStrip, 2);
	Vector2f direction;

};



