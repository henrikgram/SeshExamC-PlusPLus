#include "..\Headers\LevelManager.h"


GameObject* LevelManager::CreateObject(ObjectTag tag, float posX, float posY)
{
	//TODO: tjek hvis den ryger ud af scope.
	GameObject* go = new GameObject(Vector2<float>(posX * 96, posY * 96));
	SpriteRenderer* sr = new SpriteRenderer();
	//Collider* colider = new Collider();

	//go->position = &position;

	switch (tag)
	{
		//DECORATIONS
	case ObjectTag::FLOOR_CARPET:
		sr->SetSprite(TextureTag::FLOOR_CARPET);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::FLOOR_CARPET;
		break;

	case ObjectTag::FLOOR_WOOD:
		sr->SetSprite(TextureTag::FLOOR_WOOD);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::FLOOR_WOOD;
		break;

	case ObjectTag::WALL_DECORATION:
		sr->SetSprite(TextureTag::WALL);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::WALL_DECORATION;
		break;

	case ObjectTag::WINDOW_DECORATION:
		sr->SetSprite(TextureTag::WINDOW);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::WINDOW_DECORATION;
		break;

		//OBJECTS
	case ObjectTag::BOOKCASE:
		sr->SetSprite(TextureTag::BOOKCASE);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::BOOKCASE;
		break;

	case ObjectTag::CHEST:
		sr->SetSprite(TextureTag::CHEST);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::CHEST;
		break;

	case ObjectTag::CRATE:
		sr->SetSprite(TextureTag::CRATE);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::CRATE;
		break;

	case ObjectTag::DOOR:
		sr->SetSprite(TextureTag::DOOR);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::DOOR;
		break;

	case ObjectTag::ENEMY:
		sr->SetSprite(TextureTag::ENEMY);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::ENEMY;
		break;

	case ObjectTag::KEY:
		sr->SetSprite(TextureTag::KEY);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::KEY;
		break;

	case ObjectTag::NPC:
		sr->SetSprite(TextureTag::NPC);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::NPC;
		break;

	case ObjectTag::PLAYER:
		sr->SetSprite(TextureTag::OZZY);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::PLAYER;
		break;
		
	case ObjectTag::WINDOW:
		sr->SetSprite(TextureTag::WINDOW);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::WINDOW;
		break;

	case ObjectTag::VASE:
		sr->SetSprite(TextureTag::VASE);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::VASE;
		break;

	case ObjectTag::WALL:
		sr->SetSprite(TextureTag::WALL);
		go->AddComponent(sr);
		//go->position = new Vector2<float>(1, 1);
		*go->objectTag = ObjectTag::WALL;
		break;

	default:
		break;
	}

	go->Awake();
	go->Start();

	return go;
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

	gameObjects.insert(gameObjects.end(), objects.begin(), objects.end());

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
				gameObjects.push_back(CreateObject(ObjectTag::NPC, x, y));
			}
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

