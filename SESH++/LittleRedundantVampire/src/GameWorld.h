#pragma once
#include "GameObject.h"
#include <iostream>

#include <vector>
#include <SFML/graphics.hpp>

#include "Components/SpriteRenderer.h"
#include "Asset.h"
#include "Enum/ObjectTag.h"
#include "Components/Player.h"
#include "Components/Attack.h"
#include "Enum/ObjectTag.h"
//#include "Headers/Components/OldPlayer.h"
#include "Observer/Platform.h"
#include "GameWorld.h"
#include "Command/PlayerInvoker.h"
//#include "Headers/LevelManager.h"
#include "BitmapImage.h"
#include "LevelManager.h"

using namespace std;



class GameWorld
{
public:
	/// <summary>
	/// Returns the instance of the GameWorld class
	/// </summary>
	static GameWorld* GetInstance();

	void Run();
	vector<GameObject*>* GetGameObjects();
	vector<Collider*>* GetColliders();

	float GetScreenWidth();
	float GetScreenHeight();


private:
	static GameWorld* instance;

	vector<GameObject*>* gameObjects;


	void Initialize();
	void LoadContent();

	/// <summary>
	/// Update loop for all gameobjects
	/// </summary>
	/// <param name="timePerFrame"></param>
	void Update(Time* timePerFrame);

	/// <summary>
	/// Method for drawing all sprites into the game.
	/// </summary>
	void Draw();


	GameWorld();
	~GameWorld();

	void BootlegFactory(ObjectTag tag);
	void ResizeView(const RenderWindow& window, View& view);

	vector<Collider*>* colliders;
	Player* playerPointer;
};

