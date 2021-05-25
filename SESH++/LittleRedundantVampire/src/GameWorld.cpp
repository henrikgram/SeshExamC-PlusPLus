﻿#include "GameWorld.h"
#include "Components/AnimationComponent.h"
#include "Components/Npc.h"

//TODO: tjek om det her er fybabab
static const float VIEW_HEIGHT = 1024.0f;
View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

RenderWindow window(VideoMode(800, 800), "Little Redundant Vampire 2.0");

GameWorld::GameWorld()
{
	// TODO: Maybe move to initialize.
	movColliders = new vector<Collider*>;
	gameObjects = new vector<GameObject*>;
	colliders = new vector<Collider*>;
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
		for (auto i = gameObjects->begin(); i != gameObjects->end(); i++)
		{
			if (*i == sender)
			{
				objectsToBeDeleted.push(*i);
			}
		}
	}
	if (eventName == "ColliderDestroyed")
	{
		for (auto i = colliders->begin(); i != colliders->end();)
		{
			if (*i == sender)
			{
				i = colliders->erase(i);
			}
			else
			{
				i++;
			}
		}
	}
}

//TODO: check if this is fine, or actual factory is needed.
//TODO: RENAME. ONLY INSTANTIATE PLAYER.
void GameWorld::BootlegFactory(ObjectTag tag)
{
	//TODO: tjek hvis den ryger ud af scope.
	GameObject* go = new GameObject();
	*go->GetObjectTag() = tag;
	SpriteRenderer* sr;
	Collider* col;

	switch (tag)
	{
		//TODO: why is a scope needed here? it doesn't work without it...
	case ObjectTag::PLAYER:
	{
		sr = new SpriteRenderer(TextureTag::PLAYER_SHEET, Vector2u(1, 1), Vector2u(4, 4));

		//TODO: det her er cursed
		*go->GetPosition() = Vector2<float>(1000, 1000);
		go->AddComponent(sr);

		playerPointer = new Player();
		go->AddComponent(playerPointer);

		atckSpwnPointer = new AttackSpawner(ObjectTag::PLAYERATTACK);
		go->AddComponent(atckSpwnPointer);

		movementPointer = new Movement(5.0f, Vector2f(0.0f, 0.0f));
		go->AddComponent(movementPointer);

		AnimationComponent* aC = new AnimationComponent(sr, Vector2u(4, 4), 200.0f, 1);
		go->AddComponent(aC);

		SpriteRenderer& srRef = *sr;
		AnimationController* acController = new AnimationController(srRef, "3", "2", "0", "1", "1");
		go->AddComponent(acController);
		acController->ChangeAnimation.Attach(aC);

		//TODO: Perhaps give gameobject a size variable to make it easier to get size for the collider.
		float x = (float)sr->TextureRect->width;
		float y = (float)sr->TextureRect->height;

		col = new  Collider(Vector2f(x, y), *go->GetPosition(), 0.5f, true);
		go->AddComponent(col);
		colliders->push_back(col);
		movColliders->push_back(col);
		break;
	}

	case ObjectTag::WINDOW:
		sr = new SpriteRenderer(TextureTag::WINDOW);
		go->AddComponent(sr);
		go->SetPosition(Vector2f(1000, 800));
		go->AddComponent(new DirectionalLight(Vector2f(go->GetPosition()->x - sr->GetTexture().getSize().x / 2, 800),
			Vector2f(go->GetPosition()->x + sr->GetTexture().getSize().x / 2, 800), &walls, 90, 10));

		col = new Collider(Vector2f(1, 1), *go->GetPosition(), 1.0f, true);
		go->AddComponent(col);
		break;

	case ObjectTag::CRATE:
		sr = new SpriteRenderer(TextureTag::OZZY);
		*go->GetPosition() = Vector2f(750, 750);
		go->AddComponent(sr);
		go->AddComponent(new Platform);

		col = new  Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x,
			sr->GetSprite().getTexture()->getSize().y),
			*go->GetPosition(), 0.0f, true);
		go->AddComponent(col);
		col->AttachToColliderDestroyedEvent(GameWorld::GetInstance());
		colliders->push_back(col);
		go->AddListenerToCallSelfDestruct(GameWorld::GetInstance());
		break;
	default:
		break;
	}

	go->Awake();
	go->Start();

	//TODO: This defeats the purpose of making a Get method for the variable. Get should only be used for accessing information in a variable
	// outside of it's class, not for altering the variable.
	(*GameWorld::GetInstance()->GetGameObjects()).push_back(go);
}

void GameWorld::Initialize()
{
	BootlegFactory(ObjectTag::PLAYER);
	BootlegFactory(ObjectTag::CRATE);

	VertexArray* tmp4 = new VertexArray(sf::LinesStrip, 2);
	(*tmp4)[0].position = Vector2f(0, 0);
	(*tmp4)[0].color = Color::Red;
	(*tmp4)[1].color = Color::Red;
	(*tmp4)[1].position = Vector2f(2000, 0);

	walls.push_back(tmp4);

	VertexArray* tmp5 = new VertexArray(sf::LinesStrip, 2);
	(*tmp5)[0].position = Vector2f(2000, 0);
	(*tmp5)[0].color = Color::Red;
	(*tmp5)[1].color = Color::Red;
	(*tmp5)[1].position = Vector2f(2000, 2000);

	walls.push_back(tmp5);


	VertexArray* tmp6 = new VertexArray(sf::LinesStrip, 2);
	(*tmp6)[0].position = Vector2f(2000, 2000);
	(*tmp6)[0].color = Color::Red;
	(*tmp6)[1].color = Color::Red;
	(*tmp6)[1].position = Vector2f(0, 2000);

	walls.push_back(tmp6);

	VertexArray* tmp7 = new VertexArray(sf::LinesStrip, 2);
	(*tmp7)[0].position = Vector2f(0, 2000);
	(*tmp7)[0].color = Color::Red;
	(*tmp7)[1].color = Color::Red;
	(*tmp7)[1].position = Vector2f(0, 0);

	walls.push_back(tmp7);

	VertexArray* tmp8 = new VertexArray(sf::LinesStrip, 2);
	(*tmp8)[0].position = Vector2f(800, 1500);
	(*tmp8)[0].color = Color::Red;
	(*tmp8)[1].color = Color::Red;
	(*tmp8)[1].position = Vector2f(1100, 1500);

	walls.push_back(tmp8);

	VertexArray* cursedPlayerWall = new VertexArray(sf::LinesStrip, 2);
	(*cursedPlayerWall)[0].position = Vector2f(900, 1500);
	(*cursedPlayerWall)[0].color = Color::Red;
	(*cursedPlayerWall)[1].color = Color::Red;
	(*cursedPlayerWall)[1].position = Vector2f(1000, 1500);

	walls.push_back(cursedPlayerWall);

	VertexArray* tmp9 = new VertexArray(sf::LinesStrip, 2);
	(*tmp9)[0].position = Vector2f(8.4f*96, 7.5f*96);
	(*tmp9)[0].color = Color::Red;
	(*tmp9)[1].color = Color::Red;
	(*tmp9)[1].position = Vector2f(10.5f*96, 7.5f * 96);

	walls.push_back(tmp9);

	VertexArray* tmp10 = new VertexArray(sf::LinesStrip, 2);
	(*tmp10)[0].position = Vector2f(12.4f * 96, 13.5f * 96);
	(*tmp10)[0].color = Color::Red;
	(*tmp10)[1].color = Color::Red;
	(*tmp10)[1].position = Vector2f(14.5f * 96, 13.5f * 96);

	walls.push_back(tmp10);

	VertexArray* tmp11 = new VertexArray(sf::LinesStrip, 2);
	(*tmp11)[0].position = Vector2f(16.4f * 96, 10.5f * 96);
	(*tmp11)[0].color = Color::Red;
	(*tmp11)[1].color = Color::Red;
	(*tmp11)[1].position = Vector2f(18.5f * 96, 10.5f * 96);

	walls.push_back(tmp11);

	VertexArray* tmp12 = new VertexArray(sf::LinesStrip, 2);
	(*tmp12)[0].position = Vector2f(22 * 96, 25 * 96);
	(*tmp12)[0].color = Color::Red;
	(*tmp12)[1].color = Color::Red;
	(*tmp12)[1].position = Vector2f(23 * 96, 25 * 96);

	walls.push_back(tmp12);

	VertexArray* tmp13 = new VertexArray(sf::LinesStrip, 2);
	(*tmp13)[0].position = Vector2f(18.5f * 96, 24.5f * 96);
	(*tmp13)[0].color = Color::Red;
	(*tmp13)[1].color = Color::Red;
	(*tmp13)[1].position = Vector2f(52.5f * 96, 24.5f * 96);

	walls.push_back(tmp13);

	VertexArray* tmp14 = new VertexArray(sf::LinesStrip, 2);
	(*tmp14)[0].position = Vector2f(36.4f * 96, 16.5f * 96);
	(*tmp14)[0].color = Color::Red;
	(*tmp14)[1].color = Color::Red;
	(*tmp14)[1].position = Vector2f(38.6f * 96, 16.5f * 96);

	walls.push_back(tmp14);


	VertexArray* tmp15 = new VertexArray(sf::LinesStrip, 2);
	(*tmp15)[0].position = Vector2f(40.4f * 96, 22.5f * 96);
	(*tmp15)[0].color = Color::Red;
	(*tmp15)[1].color = Color::Red;
	(*tmp15)[1].position = Vector2f(42.6f * 96, 22.5f * 96);

	walls.push_back(tmp15);


#pragma region Damage test, Enemy and Enemy Attack on Player.
	//TODO: delete this
	//Test-attack. Can be deleted later.
	GameObject* go = new GameObject();
	SpriteRenderer* sr = new SpriteRenderer(TextureTag::ENEMY_ATTACK_SHEET, Vector2u(1, 1), Vector2u(1, 3));

	go->AddComponent(sr);

	Collider* col = new  Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x,
		sr->GetSprite().getTexture()->getSize().y),
		*go->GetPosition(), 0.0f, false);

	go->AddComponent(col);
	(*colliders).push_back(col);

	go->Awake();
	go->Start();

	*go->GetPosition() = Vector2f(1200.0f, 1000.0f);
	*go->GetObjectTag() = ObjectTag::ENEMYATTACK;

	(*gameObjects).push_back(go);

	// TODO: Test??? Maybe delete this then!
	//Test enemy damage
	GameObject* go1 = new GameObject();
	SpriteRenderer* sr1 = new SpriteRenderer(TextureTag::ENEMY);

	go1->AddComponent(sr1);

	Collider* col1 = new  Collider(Vector2f(sr1->GetSprite().getTexture()->getSize().x,
		sr1->GetSprite().getTexture()->getSize().y),
		*go1->GetPosition(), 0.0f, false);

	go1->AddComponent(col1);
	(*colliders).push_back(col1);

	go1->Awake();
	go1->Start();

	*go1->GetPosition() = Vector2f(1200.0f, 1200.0f);
	*go1->GetObjectTag() = ObjectTag::ENEMY;

	(*gameObjects).push_back(go1);

	// what this? pragma region?
#pragma endregion
}

void GameWorld::LoadContent()
{
	// Loads all textures into the game.
	Asset::GetInstance()->LoadTextures();
}

void GameWorld::DeleteObjects()
{
	int stackSize = objectsToBeDeleted.size();

	for (int i = 0; i < stackSize; i++)
	{
		GameObject* gO = objectsToBeDeleted.top();

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
		objectsToBeDeleted.pop();
	}
}

void GameWorld::Update(Time* timePerFrame)
{
	auto start = high_resolution_clock::now();

	DeleteObjects();
	vector<GameObject*>::size_type gameObjectsSize = (*GameWorld::GetInstance()->GetGameObjects()).size();

	for (auto i = (*GameWorld::GetInstance()->gameObjects).begin(); i != (*GameWorld::GetInstance()->gameObjects).end();)
	{
		vector<GameObject*>::size_type originalSize = (*GameWorld::GetInstance()->GetGameObjects()).size();

		//camera culling
		if (((*i)->GetPosition()->x - playerPointer->gameObject->GetPosition()->x) < 6 * 96 &&
			(playerPointer->gameObject->GetPosition()->x - (*i)->GetPosition()->x) < 6 * 96)
		{
			if (*(*i)->GetObjectTag() == ObjectTag::WINDOW)
			{
				(*i)->Update(timePerFrame);
			}
			else
			{
				//if it isnt a window, cull the y axis as well
				if (((*i)->GetPosition()->y - playerPointer->gameObject->GetPosition()->y) < 6 * 96 &&
					(playerPointer->gameObject->GetPosition()->y - (*i)->GetPosition()->y) < 6 * 96)
				{
					(*i)->Update(timePerFrame);
				}
			}
		}

		vector<GameObject*>::size_type updatedSize = (*GameWorld::GetInstance()->GetGameObjects()).size();

		if (originalSize == updatedSize)
		{
			++i;
		}
	}

	vector<Collider*>::iterator colIt;
	vector<Collider*>::iterator movColIt;
	for (movColIt = movColliders->begin(); movColIt < movColliders->end(); movColIt++)
	{
		if (((*movColIt)->GetPosition().x - playerPointer->gameObject->GetPosition()->x) < 3 * 96 &&
			(playerPointer->gameObject->GetPosition()->x - (*movColIt)->GetPosition().x) < 3 * 96 &&

			((*movColIt)->GetPosition().y - playerPointer->gameObject->GetPosition()->y) < 3 * 96 &&
			(playerPointer->gameObject->GetPosition()->y - (*movColIt)->GetPosition().y) < 3 * 96)
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

	if (playerPointer != nullptr)
	{
		//TODO: Fix så den tager imod attack også
		Player& playerRef = *playerPointer;
		AttackSpawner& atckSpwnPointerRef = *atckSpwnPointer;
		Movement& movementPointerRef = *movementPointer;

		PlayerInvoker::GetInstance(movementPointerRef, atckSpwnPointerRef)->InvokeCommand();
	}

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<std::chrono::microseconds>(stop - start);

	cout << "Time taken by Update(): "
		<< duration.count() << " microseconds" << endl;
}

void GameWorld::Draw()
{
	auto start = high_resolution_clock::now();
	// Clears the window.
	window.clear(Color());

	//it needs to point to something, otherwise it wont compile, because it cant delete an "empty pointer"
	//TODO: this needs to be deleted somewhere, but it dosen't work here, actually, check if it matters because its on stack.
	SpriteRenderer* sr;

	vector<GameObject*>::size_type gameObjectsSize = (*GameWorld::GetInstance()->GetGameObjects()).size();
	//iterates through the gameObjects and draws all gameobjects.
	for (vector<GameObject*>::size_type i = 0;
		i < gameObjectsSize;
		++i)
	{
		GameObject* go = (*GameWorld::GetInstance()->GetGameObjects())[i];

		//camera culling
		if (((go)->GetPosition()->x - playerPointer->gameObject->GetPosition()->x) < 6 * 96 && //right
			(playerPointer->gameObject->GetPosition()->x - (go)->GetPosition()->x) < 6 * 96) //left
		{
			if (*go->GetShouldDraw())
			{
				//TODO: downcasting is considered bad practice and dynamic casting is slow, check this for performance issues.
				sr = dynamic_cast<SpriteRenderer*>((*GameWorld::GetInstance()->GetGameObjects())[i]->GetComponent(ComponentTag::SPRITERENDERER));

				if (((go)->GetPosition()->y - playerPointer->gameObject->GetPosition()->y) < 6 * 96 &&
					(playerPointer->gameObject->GetPosition()->y - (go)->GetPosition()->y) < 6 * 96)
				{
					window.draw(sr->GetSprite());
				}

				if (*go->GetObjectTag() == ObjectTag::TEXT_BOX)
				{
					TextMessage* tm = dynamic_cast<TextMessage*>((*GameWorld::GetInstance()->GetGameObjects())[i]->GetComponent(ComponentTag::TEXT_MESSAGE));

					if (tm != nullptr)
					{
						window.draw(tm->GetMessage());
					}
					else
					{
						delete tm;
						tm = nullptr;
					}
				}
				else if (*go->GetObjectTag() == ObjectTag::WINDOW)
				{
					LightSource* light = dynamic_cast<LightSource*>((*GameWorld::GetInstance()->GetGameObjects())[i]->GetComponent(ComponentTag::LIGHT));

					if (light != nullptr)
					{

						vector<VertexArray> lightCone = light->GetLightCone();

						//TODO: this naming is ridicules
						vector<VertexArray>::iterator itttt;

						for (itttt = lightCone.begin(); itttt < lightCone.end(); itttt++)
						{
							window.draw(*itttt);
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

	//TODO: this naming is ridicules
	vector<VertexArray*>::iterator itttt;

	for (itttt = walls.begin(); itttt < walls.end(); itttt++)
	{
		window.draw(*(*itttt));
	}

	window.display();
}

void GameWorld::Run()
{
	LoadContent();
	//BootlegFactory(ObjectTag::PLAYER);
	LevelManager* lm = new LevelManager();
	*GameWorld::GetInstance()->GetGameObjects() = lm->InstantiateLevel("Level1");
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
			view.setCenter(*playerPointer->gameObject->GetPosition());
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

vector<GameObject*>* GameWorld::GetGameObjects()
{
	return gameObjects;
}

vector<Collider*>* GameWorld::GetColliders()
{
	return colliders;
}

vector<Collider*>* GameWorld::GetMovColliders()
{
	return movColliders;
}

float GameWorld::GetScreenWidth()
{
	return view.getCenter().x;
}

float GameWorld::GetScreenHeight()
{
	return view.getCenter().y - (view.getSize().y / 2);
}

void GameWorld::CloseGame()
{
	//TODO: Doesn't work, fix it.
	colliders->clear();
	for (auto i = gameObjects->begin(); i != gameObjects->end(); i++)
	{
		objectsToBeDeleted.push(*i);
	}
	DeleteObjects();
	window.close();
}

// Sets the instance to nullptr. Because static variables need a definition.
// Part of what makes the class a singleton.
GameWorld* GameWorld::instance = nullptr;
