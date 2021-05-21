#pragma once
#include <SFML/graphics.hpp>
#include <unordered_map>
#include <iostream>

#include "Enum/TextureTag.h"

using namespace sf;
using namespace std;

class Asset
{
private:
	// TODO: Bliver den gemt for evigt feat johan olsen? G�r den ud af scope? Who knows!
	unordered_map<TextureTag, Texture> textures;

	// DECORATIONS
	Texture* bookcaseTexture = new Texture;
	Texture* chestTexture = new Texture;
	Texture* crateTexture = new Texture;
	Texture* floorWoodTexture = new Texture;
	Texture* floorCarpetTexture = new Texture;
	Texture* textBoxTexture = new Texture();
	Texture* wallTexture = new Texture;
	Texture* windowTexture = new Texture;

	// OBJECTS
	Texture* playerHealthUI = new Texture;
	Texture* playerAttackSheetTexture = new Texture;
	Texture* enemyAttackSheetTexture = new Texture;
	Texture* doorTexture = new Texture;
	Texture* enemySheetTexture = new Texture;
	Texture* keyTexture = new Texture;
	Texture* npcTexture = new Texture;
	Texture* ozzyTexture = new Texture;
	Texture* playerSheetTexture = new Texture;
	Texture* vaseTexture = new Texture;


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
	Texture* GetTexture(TextureTag tag);

	/// <summary>
	/// Returns the instance of the Asset class
	/// </summary>
	static Asset* GetInstance();

	Asset();
	~Asset();
};
