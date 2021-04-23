#include "Header\Asset.h"

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

Asset::Asset()
{

}

Asset::~Asset()
{
}

