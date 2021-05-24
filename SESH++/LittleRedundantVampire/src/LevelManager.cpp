#include "LevelManager.h"
#include "GameWorld.h"
#include "Components/Enemy.h"

//TODO: maybe more commenting in this class. dunno, i guess it is pretty straight forward.

GameObject* LevelManager::CreateObject(ObjectTag tag, float posX, float posY)
{
	//TODO: tjek hvis den ryger ud af scope.
	GameObject* go = new GameObject(Vector2<float>(posX * 96, posY * 96));
	AnimationComponent* ac;
	SpriteRenderer* sr;
	Collider* col;

	float x;
	float y;

	//Determine which object to make.
	switch (tag)
	{
		//DECORATIONS
	case ObjectTag::FLOOR_CARPET:
		sr = new SpriteRenderer(TextureTag::FLOOR_CARPET);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::FLOOR_CARPET;
		break;

	case ObjectTag::FLOOR_WOOD:
		sr = new SpriteRenderer(TextureTag::FLOOR_WOOD);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::FLOOR_WOOD;
		break;

	case ObjectTag::WALL_DECORATION:
		sr = new SpriteRenderer(TextureTag::WALL);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::WALL_DECORATION;
		break;

	case ObjectTag::WINDOW_DECORATION:
		sr = new SpriteRenderer(TextureTag::WINDOW);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::WINDOW_DECORATION;
		break;

		//OBJECTS
	case ObjectTag::BOOKCASE:
		sr = new SpriteRenderer(TextureTag::BOOKCASE);
		go->AddComponent(sr);
		col = new Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->GetPosition(), 1.0f, true);
		(*GameWorld::GetInstance()->GetColliders()).push_back(col);
		go->AddComponent(col);
		*go->GetObjectTag() = ObjectTag::BOOKCASE;
		break;

	case ObjectTag::CHEST:
		sr = new SpriteRenderer(TextureTag::CHEST);
		go->AddComponent(sr);
		col = new Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->GetPosition(), 0.2f, true);
		(*GameWorld::GetInstance()->GetColliders()).push_back(col);
		go->AddComponent(col);
		*go->GetObjectTag() = ObjectTag::CHEST;
		break;

	case ObjectTag::CRATE:
	{
		sr = new SpriteRenderer(TextureTag::CRATE);

		go->AddComponent(sr);
		col = new Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->GetPosition(), 0.1f, true);
		(*GameWorld::GetInstance()->GetColliders()).push_back(col);
		(*GameWorld::GetInstance()->GetMovColliders()).push_back(col);
		go->AddComponent(col);

		GameWorld::GetInstance()->walls.push_back(col->wall);

		*go->GetObjectTag() = ObjectTag::CRATE;
		break;
	}

	case ObjectTag::DOOR:
		sr = new SpriteRenderer(TextureTag::DOOR);
		go->AddComponent(sr);
		col = new Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->GetPosition(), 1.0f, true);
		(*GameWorld::GetInstance()->GetColliders()).push_back(col);
		go->AddComponent(col);
		*go->GetObjectTag() = ObjectTag::DOOR;
		break;

	case ObjectTag::ENEMY:
		Enemy* enemy;
		sr = new SpriteRenderer(TextureTag::ENEMY, Vector2u(1, 1), Vector2u(4, 3));
		go->AddComponent(enemy = new Enemy());
		go->AddComponent(sr);
		ac = new AnimationComponent(sr, Vector2u(4, 3), 200.0f, 1);
		go->AddComponent(ac);
		x = sr->TextureRect->width;
		y = sr->TextureRect->height;
		col = new Collider(Vector2f(x, y), *go->GetPosition(), 0.5f, true);
		(*GameWorld::GetInstance()->GetColliders()).push_back(col);
		(*GameWorld::GetInstance()->GetMovColliders()).push_back(col);
		go->AddComponent(col);
		*go->GetObjectTag() = ObjectTag::ENEMY;

		GameWorld::GetInstance()->walls.push_back(col->wall);
		break;

	case ObjectTag::KEY:
		sr = new SpriteRenderer(TextureTag::KEY);
		go->AddComponent(sr);
		col = new Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->GetPosition(), 1.0f, true);
		(*GameWorld::GetInstance()->GetColliders()).push_back(col);
		go->AddComponent(col);
		*go->GetObjectTag() = ObjectTag::KEY;
		break;

	case ObjectTag::NPC:
		go->AddComponent(new Npc(new string("'V' to pick up keys!")));
		sr = new SpriteRenderer(TextureTag::NPC);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::NPC;
		col = new Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->GetPosition(), 1.0f, false);
		(*GameWorld::GetInstance()->GetColliders()).push_back(col);
		(*GameWorld::GetInstance()->GetMovColliders()).push_back(col);
		go->AddComponent(col);
		break;

	case ObjectTag::PLAYER:
		sr = new SpriteRenderer(TextureTag::OZZY);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::PLAYER;
		break;

	case ObjectTag::WINDOW:
		sr = new SpriteRenderer(TextureTag::WINDOW);
		go->AddComponent(sr);
		col = new Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->GetPosition(), 1.0f, true);
		(*GameWorld::GetInstance()->GetColliders()).push_back(col);
		go->AddComponent(col);
		*go->GetObjectTag() = ObjectTag::WINDOW;
		go->AddComponent(new DirectionalLight(Vector2f(go->GetPosition()->x - sr->GetTexture().getSize().x / 2,
			go->GetPosition()->y + sr->GetTexture().getSize().x / 2),
			Vector2f(go->GetPosition()->x + sr->GetTexture().getSize().x / 2,
			go->GetPosition()->y + sr->GetTexture().getSize().x / 2), &(GameWorld::GetInstance()->walls), 90, 10));
		break;

	case ObjectTag::VASE:
		sr = new SpriteRenderer(TextureTag::VASE);
		go->AddComponent(sr);
		col = new Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->GetPosition(), 1.0f, true);
		(*GameWorld::GetInstance()->GetColliders()).push_back(col);
		go->AddComponent(col);
		*go->GetObjectTag() = ObjectTag::VASE;
		break;

	case ObjectTag::WALL:
		sr = new SpriteRenderer(TextureTag::WALL);
		go->AddComponent(sr);
		col = new Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->GetPosition(), 1.0f, true);
		(*GameWorld::GetInstance()->GetColliders()).push_back(col);
		go->AddComponent(col);
		*go->GetObjectTag() = ObjectTag::WALL;
		break;

	default:
		break;
	}

	go->Awake();
	go->Start();

	return go;
}

vector<GameObject*> LevelManager::CreateNpcLevelOne()
{
	vector<GameObject*> gameObjects;

	GameObject* go1 = new GameObject(Vector2<float>(960, 1220));
	SpriteRenderer* sr1 = new SpriteRenderer(TextureTag::NPC, Vector2u(1, 1), Vector2u(6, 1));
	Collider* col1;

	go1->AddComponent(new Npc(new string("If you find any keys you can pick them up by pressing 'V'!")));
	go1->AddComponent(sr1);
	AnimationComponent* ac1 = new AnimationComponent(sr1, Vector2u(6, 1), 200.0f, 0);
	go1->AddComponent(ac1);
	*go1->GetObjectTag() = ObjectTag::NPC;
	float x1 = sr1->TextureRect->width;
	float y1 = sr1->TextureRect->height;
	col1 = new Collider(Vector2f(x1, y1), *go1->GetPosition(), 1.0f, false);
	(*GameWorld::GetInstance()->GetColliders()).push_back(col1);
	(*GameWorld::GetInstance()->GetMovColliders()).push_back(col1);
	go1->AddComponent(col1);

	GameObject* go2 = new GameObject(Vector2<float>(1825, 2200));
	Npc* npc2 = new Npc(new string("If you run into any hostile humans, press 'Space' to fight back!"));
	SpriteRenderer* sr2 = new SpriteRenderer(TextureTag::NPC, Vector2u(1, 1), Vector2u(6, 1));
	Collider* col2;

	go2->AddComponent(npc2);
	go2->AddComponent(sr2);
	AnimationComponent* ac2 = new AnimationComponent(sr2, Vector2u(6, 1), 200.0f, 0);
	go2->AddComponent(ac2);
	*go2->GetObjectTag() = ObjectTag::NPC;
	float x2 = sr2->TextureRect->width;
	float y2 = sr2->TextureRect->height;
	col2 = new Collider(Vector2f(x2, y2), *go2->GetPosition(), 1.0f, false);
	(*GameWorld::GetInstance()->GetColliders()).push_back(col2);
	(*GameWorld::GetInstance()->GetMovColliders()).push_back(col2);
	go2->AddComponent(col2);

	GameObject* go3 = new GameObject(Vector2<float>(2210, 545));
	Npc* npc3 = new Npc(new string("The sun sucks! B-)"));
	SpriteRenderer* sr3 = new SpriteRenderer(TextureTag::NPC, Vector2u(1,1), Vector2u(6,1));
	Collider* col3;

	go3->AddComponent(npc3);
	go3->AddComponent(sr3);
	AnimationComponent* ac3 = new AnimationComponent(sr3, Vector2u(6, 1), 200.0f, 0);
	go3->AddComponent(ac3);
	*go3->GetObjectTag() = ObjectTag::NPC;
	float x3 = sr3->TextureRect->width;
	float y3 = sr3->TextureRect->height;
	col3 = new Collider(Vector2f(x2, y2), *go3->GetPosition(), 1.0f, false);
	(*GameWorld::GetInstance()->GetColliders()).push_back(col3);
	(*GameWorld::GetInstance()->GetMovColliders()).push_back(col3);
	go3->AddComponent(col3);

	go1->Awake();
	go1->Start();
	go2->Awake();
	go2->Start();
	go3->Awake();
	go3->Start();

	gameObjects.push_back(go1);
	gameObjects.push_back(go2);
	gameObjects.push_back(go3);

	return gameObjects;
}

vector<GameObject*> LevelManager::InstantiateLevel(string levelName)
{
	vector<GameObject*> gameObjects = {};

	BitmapImage objectLayer(0, 0);
	BitmapImage decorationLayer(0, 0);

	string sObjectPath = filePath + levelName + "-ObjectLayer.bmp";
	string sDecorationPath = filePath + levelName + "-DecorationLayer.bmp";

	//converts string to char array
	const char* objectPath = sObjectPath.c_str();
	const char* decorationPath = sDecorationPath.c_str();

	objectLayer.Read(objectPath);
	decorationLayer.Read(decorationPath);

	// Runs level setup for the decoration layer first (etc. floor. Anything that has no collider).
	// Returns a vector of gameobjects.
	vector<GameObject*> decorations = LevelSetup(decorationLayer);
	// Then runs level setup for the objects that can be interacted with (anything with a collider).
	// Returns a vector of gameobjects.
	vector<GameObject*> objects = LevelSetup(objectLayer);

	// Adds all gameobjects from the decoration- and object layer to the gameobjects vector.
	gameObjects.insert(gameObjects.end(), decorations.begin(), decorations.end());
	gameObjects.insert(gameObjects.end(), objects.begin(), objects.end());

	if (levelName == "Level1")
	{
		vector<GameObject*> npcs = CreateNpcLevelOne();
		gameObjects.insert(gameObjects.end(), npcs.begin(), npcs.end());
	}

	return gameObjects;
}

vector<GameObject*> LevelManager::LevelSetup(BitmapImage& level)
{
	vector<GameObject*> gameObjects = {};

	// Get the size of the level and place down objects depending
	// on the color on the loaded bitmap.
	for (int y = 0; y < level.GetHeight(); y++)
	{
		for (int x = 0; x < level.GetWidth(); x++)
		{
			BitmapColor color = level.GetColor(x, y);

			//converts the float value (0-1) to 255
			color.b *= 255;
			color.r *= 255;
			color.g *= 255;

			// Decorations
			if (color.r == 98 && color.g == 26 && color.b == 36)
			{
				gameObjects.push_back(CreateObject(ObjectTag::FLOOR_CARPET, x, y));
			}
			else if (color.r == 205 && color.g == 170 && color.b == 96)
			{
				gameObjects.push_back(CreateObject(ObjectTag::FLOOR_WOOD, x, y));
			}
			else if (color.r == 210 && color.g == 210 && color.b == 210)
			{
				gameObjects.push_back(CreateObject(ObjectTag::WALL_DECORATION, x, y));
			}
			else if (color.r == 197 && color.g == 218 && color.b == 247)
			{
				gameObjects.push_back(CreateObject(ObjectTag::WINDOW_DECORATION, x, y));
			}

			// Objects
			else if (color.r == 96 && color.g == 62 && color.b == 57)
			{
				gameObjects.push_back(CreateObject(ObjectTag::BOOKCASE, x, y));
			}
			else if (color.r == 174 && color.g == 159 && color.b == 8)
			{
				gameObjects.push_back(CreateObject(ObjectTag::CHEST, x, y));
			}
			else if (color.r == 182 && color.g == 115 && color.b == 48)
			{
				gameObjects.push_back(CreateObject(ObjectTag::CRATE, x, y));
			}
			else if (color.r == 255 && color.g == 116 && color.b == 0)
			{
				gameObjects.push_back(CreateObject(ObjectTag::DOOR, x, y));
			}
			else if (color.r == 255 && color.g == 0 && color.b == 0)
			{
				gameObjects.push_back(CreateObject(ObjectTag::ENEMY, x, y));
			}
			else if (color.r == 255 && color.g == 220 && color.b == 0)
			{
				gameObjects.push_back(CreateObject(ObjectTag::KEY, x, y));
			}
			// TODO: Maybe delete? Or at least use the comment written below this.
			// Since NPC's are instantiated through a different method, this isn't needed for now.
			//else if (color.r == 0 && color.g == 255 && color.b == 0)
			//{
			//	gameObjects.push_back(CreateObject(ObjectTag::NPC, x, y));
			//}
			else if (color.r == 0 && color.g == 180 && color.b == 0)
			{
				gameObjects.push_back(CreateObject(ObjectTag::PLAYER, x, y));
			}
			else if (color.r == 215 && color.g == 107 && color.b == 232)
			{
				gameObjects.push_back(CreateObject(ObjectTag::VASE, x, y));
			}
			else if (color.r == 159 && color.g == 159 && color.b == 170)
			{
				gameObjects.push_back(CreateObject(ObjectTag::WALL, x, y));
			}
			else if (color.r == 151 && color.g == 183 && color.b == 238)
			{
				gameObjects.push_back(CreateObject(ObjectTag::WINDOW, x, y));
			}
		}
	}

	return gameObjects;
}