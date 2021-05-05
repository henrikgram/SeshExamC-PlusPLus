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
	case ObjectTag::PLAYER:
		sr->SetSprite(TextureTag::OZZY);
		go->AddComponent(sr);
		break;
	case ObjectTag::ENEMY:
		break;
	case ObjectTag::NPC:
		break;
	case ObjectTag::WALL:
		sr->SetSprite(TextureTag::WALL);
		go->AddComponent(sr);
		//go->position = new Vector2<float>(1, 1);
		*go->objectTag = ObjectTag::WALL;
		break;
	case ObjectTag::DOOR:
		sr->SetSprite(TextureTag::DOOR);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::DOOR;
		break;
	case ObjectTag::FLOOR:
		sr->SetSprite(TextureTag::FLOOR);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::FLOOR;
		break;
	case ObjectTag::BOOKCASE:
		sr->SetSprite(TextureTag::BOOKCASE);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::BOOKCASE;
		break;
	case ObjectTag::VASE:
		sr->SetSprite(TextureTag::VASE);
		go->AddComponent(sr);
		*go->objectTag = ObjectTag::VASE;
		break;
	case ObjectTag::WINDOW:
		break;
	case ObjectTag::CRATE:
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

	const char* objectPath = sObjectPath.c_str();
	const char* decorationPath = sDecorationPath.c_str();

	objectLayer.Read(objectPath);
	decorationLayer.Read(decorationPath);

	vector<GameObject*> objects = LevelSetup(objectLayer);
	vector<GameObject*> decorations = LevelSetup(decorationLayer);

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

			color.b *= 255;
			color.r *= 255;
			color.g *= 255;

			if (color.r == 159 && color.g == 159 && color.b == 170)
			{
				gameObjects.push_back(CreateObject(ObjectTag::WALL, x, y));
			}
			else if (color.r == 0 && color.g == 180 && color.b == 0)
			{
				gameObjects.push_back(CreateObject(ObjectTag::PLAYER, x, y));
			}
		}
	}

	return gameObjects;
}

