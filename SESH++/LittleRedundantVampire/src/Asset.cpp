#include "Headers\Asset.h"

void Asset::LoadTextures()
{
	ozzyTexture->loadFromFile("Asset/VampireOzzyStill.png");
	ozzySheetTexture->loadFromFile("Asset/OzzySheet.png");
	wallTexture->loadFromFile("Asset/StoneWall.png");
	floorTexture->loadFromFile("Asset/WoodenFloor.png");
	bookcaseTexture->loadFromFile("Asset/Bookcase.png");
	npcTexture->loadFromFile("Asset/Ghost3.png");
	textBoxTexture->loadFromFile("Asset/TextBox.png");
	textures.insert(make_pair(TextureTag::OZZY, *ozzyTexture));
	textures.insert(make_pair(TextureTag::OZZYSHEET, *ozzySheetTexture));
	textures.insert(make_pair(TextureTag::WALL, *wallTexture));
	textures.insert(make_pair(TextureTag::FLOOR, *floorTexture));
	textures.insert(make_pair(TextureTag::BOOKCASE, *bookcaseTexture));
	textures.insert(make_pair(TextureTag::NPC, *npcTexture));
	textures.insert(make_pair(TextureTag::TEXTBOX, *textBoxTexture));
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
	//TODO: tjek om man skal frigøre alle variabler inden spillet lukkes, eller det er ligegyldigt.
}

// Sets the instance to  nullptr. Because static variables need a definition.
// Part of what makes the class a singleton.
Asset* Asset::instance = nullptr;