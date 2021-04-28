#pragma once
#include <SFML/System/Vector2.hpp>

using namespace sf;

class Transform
{
public:
	Vector2<float> kylling;

	void Translate(Vector2<float> * translation);
};