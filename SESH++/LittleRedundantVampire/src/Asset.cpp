#include "Asset.h"

void Asset::LoadTextures()
{
	//DECORATIONS
	floorWoodTexture->		  loadFromFile("Asset/WoodenFloor.png");
	textBoxTexture->		  loadFromFile("Asset/TestTextBox.png");

	//OBJECTS
	playerHealthUI->		  loadFromFile("Asset/healthUI.png");
	playerAttackSheetTexture->loadFromFile("Asset/PlayerAttackSheet.png");
	enemyAttackSheetTexture-> loadFromFile("Asset/EnemyAttackSheet.png");
	bookcaseTexture->		  loadFromFile("Asset/Bookcase.png");
	chestTexture->			  loadFromFile("Asset/TreasureChest.png");
	crateTexture->			  loadFromFile("Asset/Crate.png");
	doorTexture->			  loadFromFile("Asset/DoorClosed.png");
	enemySheetTexture->	  	  loadFromFile("Asset/VillagerSheet.png");
	floorCarpetTexture->	  loadFromFile("Asset/FloorCarpet.png");
	keyTexture->			  loadFromFile("Asset/Key.png");
	npcTexture->			  loadFromFile("Asset/GhostSheet.png");
	ozzyTexture->			  loadFromFile("Asset/VampireOzzyStill.png");
	playerSheetTexture->	  loadFromFile("Asset/OzzySheet.png");
	vaseTexture->			  loadFromFile("Asset/VaseWhole.png");
	wallTexture->			  loadFromFile("Asset/StoneWall.png");	
	windowTexture->			  loadFromFile("Asset/Window.png");

	// DECORATIONS
	textures.insert(make_pair(TextureTag::FLOOR_WOOD,		   *floorWoodTexture));
	textures.insert(make_pair(TextureTag::TEXT_BOX,			   *textBoxTexture));

	//OBJECTS
	textures.insert(make_pair(TextureTag::PLAYER_HEALTH,	   *playerHealthUI));
	textures.insert(make_pair(TextureTag::PLAYER_ATTACK_SHEET, *playerAttackSheetTexture));
	textures.insert(make_pair(TextureTag::ENEMY_ATTACK_SHEET,  *enemyAttackSheetTexture));
	textures.insert(make_pair(TextureTag::BOOKCASE,			   *bookcaseTexture));
	textures.insert(make_pair(TextureTag::CHEST,			   *chestTexture));
	textures.insert(make_pair(TextureTag::CRATE,			   *crateTexture));
	textures.insert(make_pair(TextureTag::DOOR,				   *doorTexture));
	textures.insert(make_pair(TextureTag::FLOOR_CARPET,		   *floorCarpetTexture));
	textures.insert(make_pair(TextureTag::ENEMY,			   *enemySheetTexture));
	textures.insert(make_pair(TextureTag::KEY,				   *keyTexture));
	textures.insert(make_pair(TextureTag::NPC,				   *npcTexture));
	textures.insert(make_pair(TextureTag::OZZY,				   *ozzyTexture));
	textures.insert(make_pair(TextureTag::PLAYER_SHEET,		   *playerSheetTexture));
	textures.insert(make_pair(TextureTag::VASE,				   *vaseTexture));
	textures.insert(make_pair(TextureTag::WALL,				   *wallTexture));
	textures.insert(make_pair(TextureTag::WINDOW,			   *windowTexture));
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
