#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "GameObject.h"
#include <iostream>

#include <vector>
#include <stack>
#include <SFML/graphics.hpp>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

#include "Components/SpriteRenderer.h"
#include "Asset.h"
#include "Enum/ObjectTag.h"
#include "Components/Player.h"
#include "Components/Attack.h"
#include "Enum/ObjectTag.h"
#include "Observer/IListener.h"
#include "Components/Collider.h"
#include "Command/PlayerInvoker.h"
#include "Components/AttackSpawner.h"
#include "BitmapImage.h"
#include "LevelManager.h"
#include "Light/DirectionalLight.h"
#include "Components/Enemy.h"

using namespace sf;
using namespace std;
using namespace std::chrono;


/// <summary>
/// Manages everything related to running the game.
/// </summary>
class GameWorld : public IListener
{
private:
	static GameWorld* instance;

	vector<GameObject*>* gameObjects;
	stack<GameObject*>* objectsToBeDeleted;
	vector<Collider*>* colliders;
	vector<Collider*>* movColliders;

	Player* playerPointer;
	AttackSpawner* atckSpwnPointer;
	Movement* movementPointer;
	PlayerInvoker* playerInvoker;

private:
	GameWorld();
	~GameWorld();

	void ResizeView(const RenderWindow& window, View& view);

	/// <summary>
	/// Inherited via IListener.
	/// In Gameworld this is used to receive a notification from a GameObject when it's ready to be deleted during runtime.
	/// The GameObject in question is added to the stack of objectsToBeDestroyed.
	/// </summary>
	/// <param name="eventName">Name of the event.</param>
	/// <param name="sender">The sender of the event.</param>
	void OnNotify(std::string eventName, IListener* sender) override;

	void CreatePlayer();

	void Initialize();
	void LoadContent();

	/// <summary>
	/// Pops the elements in the stack of objectsToBeDeleted one by one and calls Destroy/deletes the corresponding GameObjects in the vector gameObjects
	/// </summary>
	void DeleteObjects();

	/// <summary>
	/// Update loop for all gameobjects
	/// </summary>
	/// <param name="timePerFrame">Time per every ingame frame.</param>
	void Update(Time* timePerFrame);

	/// <summary>
	/// Method for drawing all sprites into the game.
	/// </summary>
	void Draw();

public:
	void Run();

	/// <summary>
	/// Returns the instance of the GameWorld class
	/// TODO: const
	/// </summary>
	static GameWorld* GetInstance();
	// TODO: const
	vector<GameObject*>* GetGameObjects() const { return gameObjects; } //TODO: KENNETH!

	void AddToGameObjects(GameObject* go);

	stack<GameObject*>* GetObjectsToBeDeleted() const { return objectsToBeDeleted; }

	// TODO: const
	vector<Collider*>* GetColliders(); //TODO: KENNETH! This needs to be a constant, if we want to change something outside of the class it belongs to we should make a set method or something.
	// TODO: const
	vector<Collider*>* GetMovColliders();

	DirectionalLight* LightPointer;
	vector<VertexArray*> walls;

	// TODO: const
	float GetScreenWidth();
	// TODO: const
	float GetScreenHeight();

	Player* GetPlayerPointer() const { return playerPointer; }

	void CloseGame();
};

#endif