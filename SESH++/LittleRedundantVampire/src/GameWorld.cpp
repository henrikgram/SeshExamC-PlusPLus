#include "GameWorld.h"


//TODO: tjek om det her er fybabab
static const float VIEW_HEIGHT = 1024.0f;
View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

RenderWindow window(VideoMode(800, 800), "Little Redundant Vampire 2.0");


/// <summary>
/// https://www.youtube.com/watch?v=CpVbMeYryKo&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=13
/// S�rger for at det view scaler med vinduets st�rrelse. Forhindrer stretching af sprites og lignende.
/// </summary>
/// <param name="window">Spilvinduet.</param>
/// <param name="view">Det view som f�lger spilleren.</param>
void GameWorld::ResizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

//TODO: check if this is fine, or actual factory is needed
void GameWorld::BootlegFactory(ObjectTag tag)
{
	//TODO: tjek hvis den ryger ud af scope.
	GameObject* go = new GameObject();
	*go->objectTag = tag;
	SpriteRenderer* sr = new SpriteRenderer();
	Collider* col;

	switch (tag)
	{
	case ObjectTag::PLAYER:
		sr->SetSprite(TextureTag::OZZY);
		go->position = new Vector2<float>(50, 50);
		go->AddComponent(sr);
		playerPointer = new Player();
		go->AddComponent(playerPointer);
		atckSpwnPointer = new AttackSpawner(ObjectTag::PLAYERATTACK);
		go->AddComponent(atckSpwnPointer);

		//TODO: Perhaps give gameobject a size variable to make it easier to get size for the collider.
		col = new  Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->position, 0.9f, true);
		go->AddComponent(col);
		colliders.push_back(col);
		break;
	case ObjectTag::ENEMY:
		break;
	case ObjectTag::NPC:
		break;
	case ObjectTag::WALL:
		break;
	case ObjectTag::DOOR:
		break;
		//case ObjectTag::FLOOR:
		//	break;
	case ObjectTag::BOOKCASE:
		break;
	case ObjectTag::VASE:
		break;
	case ObjectTag::WINDOW:
		break;
	case ObjectTag::CRATE:
		sr->SetSprite(TextureTag::OZZY);
		go->position = new Vector2f(150, 150);
		go->AddComponent(sr);

		col = new  Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->position, 1.0f, true);
		go->AddComponent(col);
		colliders.push_back(col);
		break;
	default:
		break;
	}

	go->Awake();
	go->Start();

	(*GameWorld::GetInstance()->GetGameObjects()).push_back(go);
}

void GameWorld::Run()
{

	LoadContent();

	LevelManager* lm = new LevelManager();
	*GameWorld::GetInstance()->GetGameObjects() = lm->InstantiateLevel("Level1");

	Initialize();

	//Platform p1(nullptr, Vector2f(100, 100), Vector2f(500.0f, 500.0f));

	//Vores deltaTime er den tid der er g�et siden sidste update.
	float deltaTime = 0.0f;
	//Vi skal bruge clock til at regne ud hvor lang tid der er g�et.
	Clock clock;


	// Used for fixed update. TimePerFrame needs to be set to the amount of frames you want it to run with.
	Time timePerFrame = seconds(1.f / 60.f);
	Clock deltaClock;
	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		//Vi s�tter vores deltaTime i forhold til clock.
		deltaTime = clock.restart().asSeconds();
		// Shuts the game down when the window is closed.
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::Resized)
				ResizeView(window, view);
		}

		// For fixed update and 60 frames per second.
		// Clock is restarted to make sure we start from 0 every time.
		timeSinceLastUpdate += deltaClock.restart();

		// Once we reach 60 frames, we reset timeSinceLastUpdate, run Update(), and move the character.
		// This is to make sure the character movement speed never changes.
		//When the timesincelastUpdate is over the required amount, it runs the update, and subtracts the desired time pr frame.
		//it keeps updating until it's below the required amount, means the update is "up to date" with the game logic.
		//When it's up to date it will draw/render and refresh the display. This results in the update dosen't get behind.
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			Update(&timePerFrame);
			//p1.GetCollider().CheckCollision(player.GetCollider(), 0.1f);
			view.setCenter(*playerPointer->gameObject->position);
		}

		//Hvert gameloop korer vi Update paa vores animation.
	   //Vi korer animationen for raekke 0 (1).

		window.setView(view);

		Draw();
	}

}


void GameWorld::Initialize()
{
	BootlegFactory(ObjectTag::PLAYER);
	BootlegFactory(ObjectTag::CRATE);
}

void GameWorld::LoadContent()
{
	Asset::GetInstance()->LoadTextures();
}

void GameWorld::Update(Time* timePerFrame)
{
	vector<GameObject*>::size_type gameObjectsSize = (*GameWorld::GetInstance()->GetGameObjects()).size();
	//iterates through the gameObjects and calls update
	for (vector<GameObject*>::size_type i = 0;
		i < gameObjectsSize;
		++i)
	{
		(*GameWorld::GetInstance()->GetGameObjects())[i]->Update(timePerFrame);
	}

	vector<Collider*>::iterator colIt;
	vector<Collider*>::iterator colIt2;
	for (colIt = colliders.begin(); colIt < colliders.end(); colIt++)
	{
		for (colIt2 = colliders.begin(); colIt2 < colliders.end(); colIt2++)
		{
			if (colIt != colIt2)
			{
				(*colIt)->CheckCollision(*colIt2);
			}
		}
	}

	if (playerPointer != nullptr)
	{
		//TODO: Fix så den tager imod attack også
		Player& playerRef = *playerPointer;
		AttackSpawner& atckSpwnPointerRef = *atckSpwnPointer;

		//AttackSpawner* attackPointer = dynamic_cast<AttackSpawner*>(playerPointer->gameObject->GetComponent(ComponentTag::ATTACKSPAWNER));
		//AttackSpawner& attackRef = *attackPointer;

		PlayerInvoker::GetInstance(playerRef, atckSpwnPointerRef)->InvokeCommand();




	}
}

void GameWorld::Draw()
{
	// Clears the window.
	window.clear(Color(/*0, 255, 255, 255*/));

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

		if (*go->shouldDraw)
		{
			//TODO: downcasting is considered bad practice and dynamic casting is slow, check this for performance issues.
			sr = dynamic_cast<SpriteRenderer*>((*GameWorld::GetInstance()->GetGameObjects())[i]->GetComponent(ComponentTag::SPRITERENDERER));

			window.draw(sr->GetSprite());
		}
	}

	// Displays everything in the window.
	window.display();
}


GameWorld::GameWorld()
{
	gameObjects = new vector<GameObject*>;
}

GameWorld::~GameWorld()
{
	delete instance;
	instance = nullptr;

	delete gameObjects;
	gameObjects = nullptr;
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

vector<GameObject*>* GameWorld::GetDeletedObjects()
{
	return deletedObjects;
}


// Sets the instance to  nullptr. Because static variables need a definition.
// Part of what makes the class a singleton.
GameWorld* GameWorld::instance = nullptr;
