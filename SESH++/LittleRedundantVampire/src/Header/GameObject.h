#pragma once
#include <SFML/graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class GameObject
{


public:
	GameObject(Texture* texture);
	GameObject();
	~GameObject();

	void Update(Time * timePerFrame);
	void LoadContent();

	Sprite GetSprite();

private:
	Sprite* sprite;
};

