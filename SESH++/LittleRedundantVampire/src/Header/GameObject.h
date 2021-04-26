#pragma once
#include <SFML/graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class GameObject
{
public:
	//unordered_map<Tag, Component> components;

	GameObject(Texture* texture);
	GameObject();
	~GameObject();

	void Update(Time * timePerFrame);
	void Awake();
	void Start();
	//void AddComponent(Component * component);
	//Component * GetComponent(Tag tag);
	void Destroy();

	Sprite GetSprite();

private:
	Sprite* sprite;
};


