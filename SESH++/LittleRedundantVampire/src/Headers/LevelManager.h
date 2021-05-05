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
	/// <summary>
	/// Loads bitmaps to initiated levels. Calls LevelSetup().
	/// </summary>
	/// <param name="levelName"> Level name is used to load the correct bitmap depending on the name. </param>
	/// <returns> A list of gameObjects. </returns>
	vector<GameObject*> InstantiateLevel(string levelName);

	/// <summary>
	/// Calls CreateObject() and places the objects depending on which color and the position of that color on the bitmap.
	/// Called through InitiateLevel().
	/// </summary>
	/// <param name="level"> The picture it needs to base the level on. </param>
	/// <returns> List of gameObjects. </returns>
	vector<GameObject*> LevelSetup(BitmapImage& level);

	/// <summary>
	/// Returns an assembled object with components based on a tag.
	/// Called through LevelSetup().
	/// </summary>
	/// <param name="tag"></param>
	/// <param name="posX"></param>
	/// <param name="posY"></param>
	/// <returns></returns>
	GameObject* CreateObject(ObjectTag tag, float posX, float posY);


};

