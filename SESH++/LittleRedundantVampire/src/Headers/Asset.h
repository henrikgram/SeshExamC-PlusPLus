#pragma once
#include <SFML/graphics.hpp>
#include <unordered_map>
#include <iostream>

#include "../Enum/TextureTag.h"

using namespace sf;
using namespace std;

class Asset
{
private:
	// TODO: Bliver den gemt for evigt feat johan olsen? Går den ud af scope? Who knows!
	unordered_map<TextureTag, Texture> textures;
	Texture* ozzyTexture = new Texture;
	Texture* ozzySheetTexture = new Texture;
	Texture* attackSheetTexture = new Texture;

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