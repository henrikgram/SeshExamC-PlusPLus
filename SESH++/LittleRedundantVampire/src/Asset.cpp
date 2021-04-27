#include "Headers\Asset.h"

void Asset::LoadTextures()
{
	ozzyTexture->loadFromFile("Asset_2/VampireOzzyStill.png");
	textures.insert(make_pair(TextureTag::Ozzy, *ozzyTexture));

}

Texture* Asset::GetTexture(TextureTag tag)
{
	Texture txt;
	auto it = textures.find(tag);


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
}

// Sets the instance to  nullptr. Because static variables need a definition.
// Part of what makes the class a singleton.
Asset* Asset::instance = nullptr;