#include "Headers\Asset.h"

void Asset::LoadTextures()
{
	//DECORATIONS
	floorWoodTexture->	loadFromFile("Asset/WoodenFloor.png");

	//OBJECTS
	attackSheetTexture->loadFromFile("Asset/AttackSheet2.png");
	bookcaseTexture->	loadFromFile("Asset/Bookcase.png");
	chestTexture->		loadFromFile("Asset/TreasureChest.png");
	crateTexture->		loadFromFile("Asset/Crate.png");
	doorTexture->		loadFromFile("Asset/DoorClosed.png");
	enemyTexture->		loadFromFile("Asset/NewVillagerDown.png");
	floorCarpetTexture->loadFromFile("Asset/FloorCarpet.png");
	keyTexture->		loadFromFile("Asset/Key.png");
	npcTexture->		loadFromFile("Asset/Ghost.png");
	ozzyTexture->		loadFromFile("Asset/VampireOzzyStill.png");
	playerSheetTexture->loadFromFile("Asset/OzzySheet.png");
	vaseTexture->		loadFromFile("Asset/VaseWhole.png");
	wallTexture->		loadFromFile("Asset/StoneWall.png");	
	windowTexture->		loadFromFile("Asset/Window.png");

	// DECORATIONS
	textures.insert(make_pair(TextureTag::FLOOR_WOOD,	 *floorWoodTexture));

	//OBJECTS
	textures.insert(make_pair(TextureTag::ATTACK_SHEET,	 *attackSheetTexture));
	textures.insert(make_pair(TextureTag::BOOKCASE,		 *bookcaseTexture));
	textures.insert(make_pair(TextureTag::CHEST,		 *chestTexture));
	textures.insert(make_pair(TextureTag::CRATE,		 *crateTexture));
	textures.insert(make_pair(TextureTag::DOOR,			 *doorTexture));
	textures.insert(make_pair(TextureTag::FLOOR_CARPET,  *floorCarpetTexture));
	textures.insert(make_pair(TextureTag::ENEMY,		 *enemyTexture));
	textures.insert(make_pair(TextureTag::KEY,			 *keyTexture));
	textures.insert(make_pair(TextureTag::NPC,			 *npcTexture));
	textures.insert(make_pair(TextureTag::OZZY,			 *ozzyTexture));
	textures.insert(make_pair(TextureTag::PLAYER_SHEET,  *playerSheetTexture));
	textures.insert(make_pair(TextureTag::VASE,			 *vaseTexture));
	textures.insert(make_pair(TextureTag::WALL,			 *wallTexture));
	textures.insert(make_pair(TextureTag::WINDOW,		 *windowTexture));
}

Texture* Asset::GetTexture(TextureTag tag)
{
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
