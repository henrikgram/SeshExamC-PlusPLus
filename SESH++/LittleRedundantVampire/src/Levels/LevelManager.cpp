#include "..\Headers\LevelManager.h"


GameObject* BootlegFactory(ObjectTag tag, Vector2<float> position)
{
    //TODO: tjek hvis den ryger ud af scope.
    GameObject* go = new GameObject(position);
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

vector<GameObject*>* LevelManager::InstantiateLevel()
{
	vector<GameObject*>* gameObjects = new vector<GameObject*>;

	BitmapImage copy(0, 0);

	copy.Read("src/Levels/Test2.bmp");

	std::cout << "\n";

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			BitmapColor color = copy.GetColor(x, y);

			if (color.r == 0 && color.g == 0 && color.b == 0)
			{
                gameObjects->push_back(BootlegFactory(ObjectTag::WALL, Vector2<float>(x * 96 , y * 96 )));
				std::cout << "Wall";
			}

			else if (color.r == 0 && color.g == 1 && color.b == 0)
			{
                gameObjects->push_back(BootlegFactory(ObjectTag::PLAYER, Vector2<float>(x * 96, y * 96)));
				std::cout << "Player";
			}
		}

		std::cout << "\n";
	}


	return gameObjects;


}

