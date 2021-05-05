#include "Headers\Asset.h"

void Asset::LoadTextures()
{
	ozzyTexture->loadFromFile("Asset/VampireOzzyStill.png");
	ozzySheetTexture->loadFromFile("Asset/OzzySheet.png");
	attackSheetTexture->loadFromFile("Asset/AttackSheet2.png");
	wallTexture->loadFromFile("Asset/StoneWall.png");
	floorWoodTexture->loadFromFile("Asset/WoodenFloor.png");
	bookcaseTexture->loadFromFile("Asset/Bookcase.png");
	textures.insert(make_pair(TextureTag::OZZY, *ozzyTexture));
	textures.insert(make_pair(TextureTag::OZZYSHEET, *ozzySheetTexture));
	textures.insert(make_pair(TextureTag::ATTACKSHEET, *attackSheetTexture));
	textures.insert(make_pair(TextureTag::WALL, *wallTexture));
	textures.insert(make_pair(TextureTag::FLOOR_WOOD, *floorWoodTexture));
	textures.insert(make_pair(TextureTag::BOOKCASE, *bookcaseTexture));
}

Texture* Asset::GetTexture(TextureTag tag)
{
	Texture txt;
	unordered_map<TextureTag, Texture>::iterator it;
	it = textures.find(tag);

	return &it->second;
}

Asset* Asset::GetInstance()
{
	if (instance==nullptr)
	{
		instance = new Asset();
	}

	return instance;
}

Asset::Asset()
{

}

Asset::~Asset()
{
	//TODO: tjek om man skal frig�re alle variabler inden spillet lukkes, eller det er ligegyldigt.
}

// Sets the instance to  nullptr. Because static variables need a definition.
// Part of what makes the class a singleton.
Asset* Asset::instance = nullptr;
