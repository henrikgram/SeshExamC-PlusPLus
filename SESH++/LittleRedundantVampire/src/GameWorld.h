#pragma once
#include "GameObject.h"
#include <iostream>

#include <vector>
#include <stack>
#include <SFML/graphics.hpp>

#include "Components/SpriteRenderer.h"
#include "Asset.h"
#include "Enum/ObjectTag.h"
#include "Components/Player.h"
#include "Components/Attack.h"
#include "Enum/ObjectTag.h"
#include "Observer/Platform.h"
#include "Observer/IListener.h"
#include "Components/Collider.h"
#include "Command/PlayerInvoker.h"
#include "Components/AttackSpawner.h"
#include "BitmapImage.h"
#include "LevelManager.h"


using namespace std;



class GameWorld : protected IListener
{
public:
	/// <summary>
	/// Returns the instance of the GameWorld class
	/// </summary>
	/*static GameWorld* GetInstance();

	void Run();
	vector<GameObject*>* GetGameObjects();
	vector<Collider*>* GetColliders();

	float GetScreenWidth();
	float GetScreenHeight();

	vector<GameObject*>* GetDeletedObjects();*/


private:
	static GameWorld* instance;
	vector<GameObject*>* gameObjects;
	stack<GameObject*> objectsToBeDeleted;
	vector<Collider*>* colliders;
	Player* playerPointer;
	AttackSpawner* atckSpwnPointer;

private:
	GameWorld();
	~GameWorld();

	void ResizeView(const RenderWindow& window, View& view);

	/// <summary>
	/// Inherited via IListener.
	/// In Gameworld this is used to receive a notification from a GameObject when it's ready to be deleted during runtime.
	/// The GameObject in question is added to the stack of objectsToBeDestroyed.
	/// </summary>
	/// <param name="eventName"></param>
	/// <param name="sender"></param>
	void OnNotify(std::string eventName, IListener* sender) override;

	void BootlegFactory(ObjectTag tag);

	void Initialize();
	void LoadContent();

	/// <summary>
	/// Pops the elements in the stack of objectsToBeDeleted one by one and calls Destroy/deletes the corresponding GameObjects in the vector gameObjects
	/// </summary>
	void DeleteObjects();

	/// <summary>
	/// Update loop for all gameobjects
	/// </summary>
	/// <param name="timePerFrame"></param>
	void Update(Time* timePerFrame);

	/// <summary>
	/// Method for drawing all sprites into the game.
	/// </summary>
	void Draw();


public:
	void Run();

	/// <summary>
	/// Returns the instance of the GameWorld class
	/// </summary>
	static GameWorld* GetInstance();
	vector<GameObject*>* GetGameObjects(); //TODO: Needs to be constant otherwise we may as well make gameObjects a public.
	vector<Collider*>* GetColliders(); //TODO: This needs to be a constant, if we want to change something outside of the class it belongs to we should make a set method or something.

	/*float GetScreenWidth();
	float GetScreenHeight();
	vector<Collider*>* colliders;
	Player* playerPointer;
	AttackSpawner* atckSpwnPointer;
	Movement* movementPointer;*/
};
