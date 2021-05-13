#include "LevelManager.h"
#include "GameWorld.h"



GameObject* LevelManager::CreateObject(ObjectTag tag, float posX, float posY)
{
	//TODO: tjek hvis den ryger ud af scope.
	GameObject* go = new GameObject(Vector2<float>(posX * 96, posY * 96));
	//SpriteRenderer* sr = new SpriteRenderer();
	SpriteRenderer* sr;
	Collider* col;

	//go->position = &position;

	switch (tag)
	{
		//DECORATIONS
	case ObjectTag::FLOOR_CARPET:
		//sr->SetSprite(TextureTag::FLOOR_CARPET);
		sr = new SpriteRenderer(TextureTag::FLOOR_CARPET);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::FLOOR_CARPET;
		break;

	case ObjectTag::FLOOR_WOOD:
		//sr->SetSprite(TextureTag::FLOOR_WOOD);
		sr = new SpriteRenderer(TextureTag::FLOOR_WOOD);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::FLOOR_WOOD;
		break;

	case ObjectTag::WALL_DECORATION:
		//sr->SetSprite(TextureTag::WALL);
		sr = new SpriteRenderer(TextureTag::WALL);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::WALL_DECORATION;
		break;

	case ObjectTag::WINDOW_DECORATION:
		//sr->SetSprite(TextureTag::WINDOW);
		sr = new SpriteRenderer(TextureTag::WINDOW);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::WINDOW_DECORATION;
		break;

		//OBJECTS
	case ObjectTag::BOOKCASE:
		//sr->SetSprite(TextureTag::BOOKCASE);
		sr = new SpriteRenderer(TextureTag::BOOKCASE);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::BOOKCASE;
		break;

	case ObjectTag::CHEST:
		//sr->SetSprite(TextureTag::CHEST);
		sr = new SpriteRenderer(TextureTag::CHEST);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::CHEST;
		break;

	case ObjectTag::CRATE:
		//sr->SetSprite(TextureTag::CRATE);
		sr = new SpriteRenderer(TextureTag::CRATE);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::CRATE;
		break;

	case ObjectTag::DOOR:
		//sr->SetSprite(TextureTag::DOOR);
		sr = new SpriteRenderer(TextureTag::DOOR);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::DOOR;
		break;

	case ObjectTag::ENEMY:
		//sr->SetSprite(TextureTag::ENEMY);
		sr = new SpriteRenderer(TextureTag::ENEMY);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::ENEMY;
		break;

	case ObjectTag::KEY:
		//sr->SetSprite(TextureTag::KEY);
		sr = new SpriteRenderer(TextureTag::KEY);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::KEY;
		break;

	case ObjectTag::NPC:
		go->AddComponent(new Npc(new string("'V' to pick up keys!")));
		//sr->SetSprite(TextureTag::NPC);
		sr = new SpriteRenderer(TextureTag::NPC);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::NPC;
		col = new Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->GetPosition(), 1.0f, false);
		(*GameWorld::GetInstance()->GetColliders()).push_back(col);
		go->AddComponent(col);
		break;

	case ObjectTag::PLAYER:
		//sr->SetSprite(TextureTag::OZZY);
		sr = new SpriteRenderer(TextureTag::OZZY);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::PLAYER;
		break;

	case ObjectTag::WINDOW:
		//sr->SetSprite(TextureTag::WINDOW);
		sr = new SpriteRenderer(TextureTag::WINDOW);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::WINDOW;
		break;

	case ObjectTag::VASE:
		//sr->SetSprite(TextureTag::VASE);
		sr = new SpriteRenderer(TextureTag::VASE);
		go->AddComponent(sr);
		*go->GetObjectTag() = ObjectTag::VASE;
		break;

	case ObjectTag::WALL:
		//sr->SetSprite(TextureTag::WALL);
		sr = new SpriteRenderer(TextureTag::WALL);
		go->AddComponent(sr);
		//go->position = new Vector2<float>(1, 1);
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

	GameObject* go1 = new GameObject(Vector2<float>(1000, 1300));
	//Npc* npc1 = new Npc(new string("'V' to pick up keys!"));
	SpriteRenderer* sr1 = new SpriteRenderer(TextureTag::NPC);
	Collider* col1;
	go1->AddComponent(new Npc(new string("'V' to pick up keys!")));
	//sr1->SetSprite(TextureTag::NPC);
	go1->AddComponent(sr1);
	*go1->GetObjectTag() = ObjectTag::NPC;
	col1 = new Collider(Vector2f(sr1->GetSprite().getTexture()->getSize().x, sr1->GetSprite().getTexture()->getSize().y), *go1->GetPosition(), 1.0f, false);
	(*GameWorld::GetInstance()->GetColliders()).push_back(col1);
	go1->AddComponent(col1);

	GameObject* go2 = new GameObject(Vector2<float>(3000, 500));
	Npc* npc2 = new Npc(new string("Fuck you in particular."));
	SpriteRenderer* sr2 = new SpriteRenderer(TextureTag::NPC);
	Collider* col2;
	go2->AddComponent(npc2);
	//sr2->SetSprite(TextureTag::NPC);
	go2->AddComponent(sr2);
	*go2->GetObjectTag() = ObjectTag::NPC;
	col2 = new Collider(Vector2f(sr2->GetSprite().getTexture()->getSize().x, sr2->GetSprite().getTexture()->getSize().y), *go2->GetPosition(), 1.0f, false);
	(*GameWorld::GetInstance()->GetColliders()).push_back(col2);
	go2->AddComponent(col2);

	GameObject* go3 = new GameObject(Vector2<float>(1000, 1500));
	Npc* npc3 = new Npc(new string("Ghost boi, BOO!"));
	SpriteRenderer* sr3 = new SpriteRenderer(TextureTag::NPC);
	Collider* col3;
	go3->AddComponent(npc3);
	//sr3->SetSprite(TextureTag::NPC);
	go3->AddComponent(sr3);
	*go3->GetObjectTag() = ObjectTag::NPC;
	col3 = new Collider(Vector2f(sr3->GetSprite().getTexture()->getSize().x, sr3->GetSprite().getTexture()->getSize().y), *go3->GetPosition(), 1.0f, false);
	(*GameWorld::GetInstance()->GetColliders()).push_back(col3);
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

	vector<GameObject*> decorations = LevelSetup(decorationLayer);
	vector<GameObject*> objects = LevelSetup(objectLayer);

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
			else if (color.r == 0 && color.g == 255 && color.b == 0)
			{
				//gameObjects.push_back(CreateObject(ObjectTag::NPC, x, y));
			}
			if (color.r == 0 && color.g == 180 && color.b == 0)
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
