#include <iostream>
#include <vector>
#include <SFML/graphics.hpp>

#include "Headers/Components/SpriteRenderer.h"
#include "Headers/GameObject.h"
#include "Headers/Asset.h"
#include "Enum/ObjectTag.h"
#include "Headers/Components/Player.h"
#include "Headers/Components/Attack.h"
#include "Enum/ObjectTag.h"
//#include "Headers/Components/OldPlayer.h"
#include "Headers/Platform.h"
#include "Headers/Global.h"
#include "Headers/Command/PlayerInvoker.h"
//#include "Headers/LevelManager.h"
#include "Headers/BitmapImage.h"
#include "Headers/LevelManager.h"

using namespace std;
using namespace sf;
static const float VIEW_HEIGHT = 1024.0f;


RenderWindow window(VideoMode(800, 800), "Little Redundant Vampire 2.0");
View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));


//TODO: check if heap or stack
//vector<GameObject>::iterator it;
//vector<GameObject> gameObjects = Global::GetInstance()->GetGameObjects();

//const vector<GameObject>& gameObjects = Global::GetGameObjects();

vector<Collider*> colliders;


Player* playerPointer;



/// <summary>
/// https://www.youtube.com/watch?v=CpVbMeYryKo&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=13
/// S�rger for at det view scaler med vinduets st�rrelse. Forhindrer stretching af sprites og lignende.
/// </summary>
/// <param name="window">Spilvinduet.</param>
/// <param name="view">Det view som f�lger spilleren.</param>
void ResizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

//TODO: check if this is fine, or actual factory is needed
void BootlegFactory(ObjectTag tag)
{
	//TODO: tjek hvis den ryger ud af scope.
	GameObject* go = new GameObject();
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

		//TODO: Perhaps give gameobject a size variable to make it easier to get size for the collider.
		col = new  Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->position, 0.5f, true);
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

	col = new  Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->position, 0.5f, false);
	go->AddComponent(col);
	colliders.push_back(col);
		break;
	default:
		break;
	}

	go->Awake();
	go->Start();

	(*Global::GetInstance()->GetGameObjects()).push_back(go);
}


void LoadContent()
{
	Asset::GetInstance()->LoadTextures();
}

void Initialize()
{
    BootlegFactory(ObjectTag::PLAYER);
    BootlegFactory(ObjectTag::CRATE);
}

// TODO: Pointer fix. Check if it works correctly. Check if double pointers necessary

/// <summary>
/// Update loop for all gameobjects
/// </summary>
/// <param name="timePerFrame"></param>
void Update(Time* timePerFrame)
{
	vector<GameObject*>::size_type gameObjectsSize = (*Global::GetInstance()->GetGameObjects()).size();
	//iterates through the gameObjects and calls update
	for (vector<GameObject*>::size_type i = 0;
		i < gameObjectsSize;
		++i)
	{
		(*Global::GetInstance()->GetGameObjects())[i]->Update(timePerFrame);
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

	Player& playerRef = *playerPointer;

	PlayerInvoker::GetInstance(playerRef)->InvokeCommand();
}

/// <summary>
/// Method for drawing all sprites into the game.
/// </summary>
void Draw()
{
	// Clears the window.
	window.clear(Color(0, 255, 255, 255));

	//it needs to point to something, otherwise it wont compile, because it cant delete an "empty pointer"
	//TODO: this needs to be deleted somewhere, but it dosen't work here, actually, check if it matters because its on stack.
	SpriteRenderer* sr;

	vector<GameObject*>::size_type gameObjectsSize = (*Global::GetInstance()->GetGameObjects()).size();
	//iterates through the gameObjects and draws all gameobjects.
	for (vector<GameObject*>::size_type i = 0;
		i < gameObjectsSize;
		++i)
	{
		//TODO: downcasting is considered bad practice and dynamic casting is slow, check this for performance issues.
		sr = dynamic_cast<SpriteRenderer*>((*Global::GetInstance()->GetGameObjects())[i]->GetComponent(ComponentTag::SPRITERENDERER));

		window.draw(sr->GetSprite());
	}
	// Displays everything in the window.
	window.display();
}

/// <summary>
/// Everything is run from here.
/// </summary>
/// <returns></returns>
int main()
{
	LoadContent();
	Initialize();
	
	LevelManager* lm = new LevelManager();
	gameObjects = lm->InstantiateLevel("Level1");

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
			//player.Update(deltaTime);
			//p1.GetCollider().CheckCollision(player.GetCollider(), 0.1f);
			//view.setCenter(player.GetPosition());
		}

		//Hvert gameloop korer vi Update paa vores animation.
	   //Vi korer animationen for raekke 0 (1).

		//window.setView(view);

		Draw();
		//window.clear(Color(0, 255, 255, 255));
		//player.Draw(window);
		//p1.Draw(window);
		//window.display();
	}

	return 0;
}
