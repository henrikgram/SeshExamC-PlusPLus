#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <iostream>
#include "BitmapImage.h"
#include "GameObject.h"
#include "Enum/TextureTag.h"
#include "Components/SpriteRenderer.h"
#include "Components/Collider.h"
#include "Components/Npc.h"
#include "Components/AnimationComponent.h"

using namespace std;


/// <summary>
/// Manages creation of levels.
/// </summary>
class LevelManager
{
private:
	//Where the bitmap-images are located.
	string filePath = "Levels/";

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
	/// <param name="tag">tag of the created object</param>
	/// <param name="posX">x position</param>
	/// <param name="posY">y position</param>
	/// <returns></returns>
	GameObject* CreateObject(ObjectTag tag, float posX, float posY);

	/// <summary>
	/// Instantiates all NPC for the first level.
	/// TODO:*This isn't the best way to do this, but we didn't have time to implement a better solution.
	/// </summary>
	GameObject* CreateNpcLevelOne(string msg, Vector2f position);
};

#endif