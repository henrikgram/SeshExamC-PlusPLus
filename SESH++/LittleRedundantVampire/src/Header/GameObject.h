#pragma once
#include <SFML/graphics.hpp>
using namespace sf;
using namespace std;

class GameObject
{
public:
	GameObject(Texture texture);
	~GameObject();

	void Update(Time timePerFrame);
	void LoadContent();

private:
};

