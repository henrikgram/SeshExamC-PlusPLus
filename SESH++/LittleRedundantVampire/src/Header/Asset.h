#pragma once
#include <SFML/graphics.hpp>
#include "Enum/TextureTag.h"
#include <unordered_map>
#include <iostream>

using namespace sf;
using namespace std;

class Asset
{
private:
	//unordered_map<string, Texture> myKeys, MyValues;
	// TODO: Bliver den gemt for evigt feat johan olsen? Går den ud af scope? Who knows!
	unordered_map<TextureTag, Texture> textures/* = new unordered_map<TextureTag, Texture>*/;
	Texture* ozzyTexture = new Texture;
public:
	void LoadTextures();
	Texture* GetTexture(TextureTag tag);
	Asset();
	~Asset();
};