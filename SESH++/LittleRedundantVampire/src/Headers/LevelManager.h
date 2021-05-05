#pragma once
#include <iostream>
#include "BitmapImage.h"
#include "GameObject.h"
#include "../Enum/TextureTag.h"
#include "Components/SpriteRenderer.h"

using namespace std;


class LevelManager
{
private:
	string filePath = "src/Levels/";

public:
	vector<GameObject*>* InstantiateLevel(string levelName);
	vector<GameObject*>* LevelSetup(BitmapImage& level);
	GameObject* CreateObject(ObjectTag tag, float posX, float posY);


};

