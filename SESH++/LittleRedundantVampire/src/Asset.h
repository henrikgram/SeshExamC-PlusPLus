#ifndef ASSET_H
#define ASSET_H

#include <SFML/graphics.hpp>
#include <unordered_map>
#include <iostream>

#include "Enum/TextureTag.h"

using namespace sf;
using namespace std;


/// <summary>
/// Manages assets. Also manages loading assets.
/// </summary>
class Asset
{
private:
	unordered_map<TextureTag, Texture*> textures;

	// DECORATIONS
	Texture* bookcaseTexture;
	Texture* chestTexture;
	Texture* crateTexture;
	Texture* floorWoodTexture;
	Texture* floorCarpetTexture;
	Texture* textBoxTexture;
	Texture* wallTexture;
	Texture* windowTexture;

	// OBJECTS
	Texture* playerHealthUI;
	Texture* playerAttackSheetTexture;
	Texture* enemyAttackSheetTexture;
	Texture* doorTexture;
	Texture* enemySheetTexture;
	Texture* keyTexture;
	Texture* npcTexture;
	Texture* ozzyTexture;
	Texture* playerSheetTexture;
	Texture* vaseTexture;

	// Part of what makes the class a singleton.
	static Asset* instance;

public:
	/// <summary>
	/// Loads all the textures into the program so we can access and apply them.
	/// </summary>
	void LoadTextures();

	/// <summary>
	/// Gets a texture based on TextureTag.
	/// </summary>
	Texture* FetchTexture(TextureTag tag);

	/// <summary>
	/// Returns the instance of the Asset class
	/// </summary>
	static Asset* GetInstance();

	Asset();
	~Asset();
};

#endif