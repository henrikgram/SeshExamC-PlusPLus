#include "Header/GameObject.h"
using namespace sf;
using namespace std;

GameObject::GameObject(Texture* texture)
{
	sprite = new Sprite;
	sprite->setTexture(*texture);
}

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Update(Time * timePerFrame)
{
	//cout << "UPDATING \n";
}

void GameObject::LoadContent()
{

}

//TODO: check if correct reference?
Sprite GameObject::GetSprite()
{
	return *sprite;
}
