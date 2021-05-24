#pragma once
#include <SFML/Graphics.hpp>
#include "../Component.h"
using namespace sf;

//TODO: delete this
class Platform : public Component
{
public:
	Platform(/*Texture* texture, Vector2f size, Vector2f position*/);
	~Platform();

	/// <summary>
/// Tegner platformens sprite.
/// </summary>
/// <param name="window">Det vindue som vi skal render sprite i.</param>
	//void Draw(RenderWindow& window);
	//TODO: whats dis

	//Collider GetCollider() { return Collider(body); }

private:
	//string* something;

	// Inherited via Component
	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;
	float* timer;
};

