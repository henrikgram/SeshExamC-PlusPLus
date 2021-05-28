#include "GameWorld.h"
#include "Components/AnimationComponent.h"
#include "Components/Npc.h"
#include <Windows.h>

// Camera code.
const float VIEW_HEIGHT = 1024.0f;
View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

RenderWindow window(VideoMode(800, 800), "Little Redundant Vampire 2.0");

GameWorld::GameWorld()
{
	movColliders = new vector<Collider*>;
	gameObjects = new vector<GameObject*>;
	colliders = new vector<Collider*>;
	objectsToBeDeleted = new stack<GameObject*>;
}

GameWorld::~GameWorld()
{
	delete instance;
	instance = nullptr;

	delete gameObjects;
	gameObjects = nullptr;

	delete movColliders;
	movColliders = nullptr;

	delete colliders;
	colliders = nullptr;
}

/// <summary>
/// https://www.youtube.com/watch?v=CpVbMeYryKo&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=13
/// Scales game window size with the screen size.
/// </summary>
/// <param name="window">Game window</param>
/// <param name="view">The view following the player.</param>
void GameWorld::ResizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void GameWorld::OnNotify(std::string eventName, IListener* sender)
{
	if (eventName == "DeleteObject")
	{
		GameObject* go = *find(gameObjects->begin(), gameObjects->end(), sender);
		if (go != nullptr)
		{
			objectsToBeDeleted->push(go);
		}
	}
	if (eventName == "ColliderDestroyed")
	{
		vector<Collider*>::iterator it;
		it = find(colliders->begin(), colliders->end(), sender);
		if (it != colliders->end())
		{
			vector<VertexArray*>::iterator wallIt;
			wallIt = find(walls.begin(), walls.end(), (*it)->Wall);
			if (wallIt != walls.end())
			{
				walls.erase(wallIt);
			}
			colliders->erase(it);
		}

		// Earases the first thing it finds on the list. If there are duplicates, it won't find them and delete them.
		// We don't have duplicates at the time, so this would be okay to use too.
		it = find(movColliders->begin(), movColliders->end(), sender);
		if (it != movColliders->end())
		{
			movColliders->erase(it);
		}

		// Below line of code erases every instance that matches the sender.
		// We currently don't have duplicates, but this might be nice if we are ever unsure whether or not there will be duplicates.
		//movColliders->erase(std::remove(movColliders->begin(), movColliders->end(), sender), movColliders->end());
	}
}

void GameWorld::CreatePlayer()
{
	GameObject* go = new GameObject();
	go->SetObjectTag(ObjectTag::PLAYER);
	SpriteRenderer* sr;
	Collider* col;

	sr = new SpriteRenderer(TextureTag::PLAYER_SHEET, Vector2u(1, 1), Vector2u(4, 4));

	go->SetPosition(Vector2<float>(1000, 1000));
	go->AddComponent(sr);

	playerPointer = new Player();
	go->AddComponent(playerPointer);

	atckSpwnPointer = new AttackSpawner(ObjectTag::PLAYERATTACK);
	go->AddComponent(atckSpwnPointer);

	movementPointer = new Movement(5.0f, Vector2f(0.0f, 0.0f));
	go->AddComponent(movementPointer);

	AttackSpawner& atckSpwnPointerRef = *atckSpwnPointer;
	Movement& movementPointerRef = *movementPointer;

	playerInvoker = new PlayerInvoker(movementPointerRef, atckSpwnPointerRef);

	AnimationComponent* aC = new AnimationComponent(sr, Vector2u(4, 4), 200.0f, 1);
	go->AddComponent(aC);

	SpriteRenderer& srRef = *sr;
	AnimationController* acController = new AnimationController(srRef, "3", "2", "0", "1", "1");
	go->AddComponent(acController);
	acController->AttachListenerToChangeAnimation(aC);

	float x = (float)sr->GetTextureRect().width;
	float y = (float)sr->GetTextureRect().height;

	col = new  Collider(Vector2f(x, y), go->GetPosition(), 0.5f, true);
	go->AddComponent(col);
	colliders->push_back(col);
	movColliders->push_back(col);

	gameObjects->push_back(go);
}

void GameWorld::Initialize()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	LevelManager* lm = new LevelManager();
	*gameObjects = lm->InstantiateLevel("Level1");

	CreatePlayer();

	vector<GameObject*>::iterator it;

	for (it = gameObjects->begin(); it < gameObjects->end(); it++)
	{
		if ((*it)->GetObjectTag() == ObjectTag::ENEMY)
		{
			Enemy* e;
			e = dynamic_cast<Enemy*>((*it)->GetComponent(ComponentTag::ENEMY));

			e->SetTarget(playerPointer->gameObject);
		}
	}

	for (it = gameObjects->begin(); it < gameObjects->end(); it++)
	{
		(*it)->Awake();
	}

	for (it = gameObjects->begin(); it < gameObjects->end(); it++)
	{
		(*it)->Start();
	}


	//Hardcoded walls so light intersects with the objects
	//TODO:* this should be calculated dynamically.
	VertexArray* bookCaseWall1 = new VertexArray(sf::LinesStrip, 2);
	(*bookCaseWall1)[0].position = Vector2f(8.4f * 96, 7.5f * 96);
	(*bookCaseWall1)[0].color = Color::Red;
	(*bookCaseWall1)[1].color = Color::Red;
	(*bookCaseWall1)[1].position = Vector2f(10.5f * 96, 7.5f * 96);

	walls.push_back(bookCaseWall1);

	VertexArray* bookCaseWall2 = new VertexArray(sf::LinesStrip, 2);
	(*bookCaseWall2)[0].position = Vector2f(12.4f * 96, 13.5f * 96);
	(*bookCaseWall2)[0].color = Color::Red;
	(*bookCaseWall2)[1].color = Color::Red;
	(*bookCaseWall2)[1].position = Vector2f(14.5f * 96, 13.5f * 96);

	walls.push_back(bookCaseWall2);

	VertexArray* bookCaseWall3 = new VertexArray(sf::LinesStrip, 2);
	(*bookCaseWall3)[0].position = Vector2f(16.4f * 96, 10.5f * 96);
	(*bookCaseWall3)[0].color = Color::Red;
	(*bookCaseWall3)[1].color = Color::Red;
	(*bookCaseWall3)[1].position = Vector2f(18.5f * 96, 10.5f * 96);

	walls.push_back(bookCaseWall3);

	VertexArray* longWallPuzzleSection = new VertexArray(sf::LinesStrip, 2);
	(*longWallPuzzleSection)[0].position = Vector2f(16.5f * 96, 24.5f * 96);
	(*longWallPuzzleSection)[0].color = Color::Red;
	(*longWallPuzzleSection)[1].color = Color::Red;
	(*longWallPuzzleSection)[1].position = Vector2f(45.5f * 96, 24.5f * 96);

	walls.push_back(longWallPuzzleSection);

	VertexArray* EnemyAreaWall1 = new VertexArray(sf::LinesStrip, 2);
	(*EnemyAreaWall1)[0].position = Vector2f(36.4f * 96, 16.5f * 96);
	(*EnemyAreaWall1)[0].color = Color::Red;
	(*EnemyAreaWall1)[1].color = Color::Red;
	(*EnemyAreaWall1)[1].position = Vector2f(38.6f * 96, 16.5f * 96);

	walls.push_back(EnemyAreaWall1);


	VertexArray* EnemyAreaWall2 = new VertexArray(sf::LinesStrip, 2);
	(*EnemyAreaWall2)[0].position = Vector2f(40.4f * 96, 22.5f * 96);
	(*EnemyAreaWall2)[0].color = Color::Red;
	(*EnemyAreaWall2)[1].color = Color::Red;
	(*EnemyAreaWall2)[1].position = Vector2f(42.6f * 96, 22.5f * 96);

	walls.push_back(EnemyAreaWall2);

	sound.setBuffer(buffer);
	sound.setLoop(true);
	sound.play();
}

void GameWorld::LoadContent()
{
	// Loads all textures into the game.
	Asset::GetInstance()->LoadTextures();
	buffer.loadFromFile("Asset/Sly2OSTprague.ogg");
}

void GameWorld::DeleteObjects()
{
	int stackSize = objectsToBeDeleted->size();

	for (int i = 0; i < stackSize; i++)
	{
		GameObject* gO = objectsToBeDeleted->top();
		//TODO:* Maybe use find or remove_if instead.
		for (auto i = gameObjects->begin(); i != gameObjects->end();)
		{
			if (*i == gO)
			{
				(*i)->Destroy();
				delete (*i);
				*i = nullptr;
				i = gameObjects->erase(i);
			}
			else
			{
				i++;
			}
		}
		objectsToBeDeleted->pop();
	}
}

void GameWorld::Update(Time* timePerFrame)
{
	auto start = high_resolution_clock::now();

	DeleteObjects();

	vector<Collider*>::iterator colIt;
	vector<Collider*>::iterator movColIt;
	for (movColIt = movColliders->begin(); movColIt < movColliders->end(); movColIt++)
	{
		if (((*movColIt)->GetPosition().x - playerPointer->gameObject->GetPosition().x) < 3 * 96 &&
			(playerPointer->gameObject->GetPosition().x - (*movColIt)->GetPosition().x) < 3 * 96 &&

			((*movColIt)->GetPosition().y - playerPointer->gameObject->GetPosition().y) < 3 * 96 &&
			(playerPointer->gameObject->GetPosition().y - (*movColIt)->GetPosition().y) < 3 * 96)
		{
			for (colIt = colliders->begin(); colIt < colliders->end(); colIt++)
			{
				if (*movColIt != *colIt)
				{
					(*movColIt)->CheckCollision(*colIt);
				}
			}
		}
	}
	vector<GameObject*>::size_type gameObjectsSize = gameObjects->size();

	for (auto i = gameObjects->begin(); i != gameObjects->end();)
	{
		vector<GameObject*>::size_type originalSize = gameObjects->size();

		//camera culling
		if (((*i)->GetPosition().x - playerPointer->gameObject->GetPosition().x) < 6 * 96 &&
			(playerPointer->gameObject->GetPosition().x - (*i)->GetPosition().x) < 6 * 96)
		{
			if ((*i)->GetObjectTag() == ObjectTag::WINDOW)
			{
				(*i)->Update(timePerFrame);
			}
			else
			{
				//if it isnt a window, cull the y axis as well
				if (((*i)->GetPosition().y - playerPointer->gameObject->GetPosition().y) < 6 * 96 &&
					(playerPointer->gameObject->GetPosition().y - (*i)->GetPosition().y) < 6 * 96)
				{
					(*i)->Update(timePerFrame);
				}
			}
		}

		vector<GameObject*>::size_type updatedSize = gameObjects->size();

		if (originalSize == updatedSize)
		{
			++i;
		}
	}

	playerInvoker->InvokeCommand();

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<std::chrono::microseconds>(stop - start);
	 // For debugging.
	//std::cout << "Time taken by Update(): "
	//	<< duration.count() << " microseconds" << endl;
}

void GameWorld::Draw()
{
	auto start = high_resolution_clock::now();
	// Clears the window.
	window.clear(Color());

	SpriteRenderer* sr;

	vector<GameObject*>::size_type gameObjectsSize = gameObjects->size();
	//iterates through the gameObjects and draws all gameobjects.
	for (vector<GameObject*>::size_type i = 0;
		i < gameObjectsSize;
		++i)
	{
		GameObject* go = gameObjects->at(i);

		//camera culling
		if (((go)->GetPosition().x - playerPointer->gameObject->GetPosition().x) < 6 * 96 && //right
			(playerPointer->gameObject->GetPosition().x - (go)->GetPosition().x) < 6 * 96) //left
		{
			if (go->GetShouldDraw())
			{
				sr = dynamic_cast<SpriteRenderer*>(gameObjects->at(i)->GetComponent(ComponentTag::SPRITERENDERER));

				if (((go)->GetPosition().y - playerPointer->gameObject->GetPosition().y) < 6 * 96 &&
					(playerPointer->gameObject->GetPosition().y - (go)->GetPosition().y) < 6 * 96)
				{
					window.draw(sr->GetSprite());
				}

				if (go->GetObjectTag() == ObjectTag::TEXT_BOX)
				{
					TextMessage* tm = dynamic_cast<TextMessage*>(gameObjects->at(i)->GetComponent(ComponentTag::TEXT_MESSAGE));

					if (tm != nullptr)
					{
						window.draw(tm->GetTextMessage());
					}
					else
					{
						delete tm;
						tm = nullptr;
					}
				}
				else if (go->GetObjectTag() == ObjectTag::WINDOW)
				{
					LightSource* light = dynamic_cast<LightSource*>(gameObjects->at(i)->GetComponent(ComponentTag::LIGHT));

					if (light != nullptr)
					{
						vector<VertexArray> lightCone = light->GetLightCone();

						vector<VertexArray>::iterator it;

						for (it = lightCone.begin(); it < lightCone.end(); it++)
						{
							window.draw(*it);
						}
					}
					else
					{
						delete light;
						light = nullptr;
					}
				}
			}
		}
	}

	//TODO:* For debugging. Remove before release
	//vector<VertexArray*>::iterator it;

	//for (it = walls.begin(); it < walls.end(); it++)
	//{
	//	window.draw(*(*it));
	//}

	window.display();
}

void GameWorld::Run()
{
	LoadContent();
	Initialize();

	//Time since last update.
	float deltaTime = 0.0f;
	//Clock to determine time.
	Clock clock;

	// Used for fixed update. TimePerFrame needs to be set to the amount of frames you want it to run with.
	Time timePerFrame = sf::seconds(1.f / 60.f);
	Clock deltaClock;
	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			CloseGame();
			break;
		}

		//deltatime set to match clock.
		deltaTime = clock.restart().asSeconds();

		// For fixed update and 60 frames per second.
		// Clock is restarted to make sure we start from 0 every time.
		timeSinceLastUpdate += deltaClock.restart();

		// Once we reach 60 frames, we reset timeSinceLastUpdate, run Update(), and move the character.
		// This is to make sure the character movement speed never changes.
		//When the timesincelastUpdate is over the required amount, it runs the update, and subtracts the desired time pr frame.
		//it keeps updating until it's below the required amount, means the update is "up to date" with the game logic.
		//When it's up to date it will draw/render and refresh the display. This ensures that the update dosen't get behind.
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			Update(&timePerFrame);
			view.setCenter(playerPointer->gameObject->GetPosition());
		}

		//The view you see in the window.
		window.setView(view);

		Draw();

		// Shuts the game down when the window is closed.
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				CloseGame();
			}
			if (event.type == Event::Resized)
			{
				ResizeView(window, view);
			}
		}
	}
}


GameWorld* GameWorld::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new GameWorld();
	}

	return instance;
}

vector<GameObject*>* GameWorld::GetGameObjects() const
{
	return gameObjects;
}

vector<Collider*> GameWorld::GetColliders() const
{
	return *colliders;
}

void GameWorld::AddToColliders(Collider* collider)
{
	colliders->push_back(collider);
}

vector<Collider*> GameWorld::GetMovColliders() const
{
	return *movColliders;
}

void GameWorld::AddToMovColliders(Collider* collider)
{
	movColliders->push_back(collider);
}

float GameWorld::GetScreenWidth() const
{
	return view.getCenter().x;
}

float GameWorld::GetScreenHeight() const
{
	return view.getCenter().y - (view.getSize().y / 2);
}

void GameWorld::CloseGame()
{
	//Clear the stack of objectsToBeDeleted.
	int stackSize = objectsToBeDeleted->size();

	for (int i = 0; i < stackSize; i++)
	{
		objectsToBeDeleted->pop();
	}

	//Call Destroy on and delete every gameObject.
	int gameObjectsAmount = gameObjects->size();
	for (int i = 0; i < gameObjectsAmount; i++)
	{
		gameObjects->at(i)->Destroy();
		delete gameObjects->at(i);
		gameObjects->at(i) = nullptr;
	}

	gameObjects->clear();
	colliders->clear();
	movColliders->clear();

	delete Asset::GetInstance();

	delete playerInvoker;
	playerInvoker = nullptr;

	int wallAmount = walls.size();
	for (int i = 0; i < wallAmount; i++)
	{
		delete walls.at(i);
		walls.at(i) = nullptr;
	}

	walls.clear();

	window.close();
}

// Sets the instance to nullptr. Because static variables need a definition.
// Part of what makes the class a singleton.
GameWorld* GameWorld::instance = nullptr;
