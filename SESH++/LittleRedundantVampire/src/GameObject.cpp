#include "Headers/GameObject.h"
#include "Headers/Component.h"
using namespace sf;
using namespace std;

//GameObject::GameObject(Texture* texture)
//{
//	sprite = new Sprite;
//	sprite->setTexture(*texture);
//}

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Update(Time* timePerFrame)
{

}

void GameObject::Awake()
{

}

void GameObject::Start()
{

}

void GameObject::AddComponent(Component* component)
{
	components.insert(make_pair(component->ToEnum(), component));
}

Component* GameObject::GetComponent(ComponentTag tag)
{
	return components[tag];
}

//template <typename T> T GetComponent2(ComponentTag tag)
//{
//	return components[tag];
//}

void GameObject::Destroy()
{
}

//TODO: check if correct reference? memoryleak?
//Sprite GameObject::GetSprite()
//{
//	return *sprite;
//}
