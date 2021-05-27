#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "../Component.h"
#include "../Enum/TextureTag.h"
#include "../Asset.h"

using namespace sf;


/// <summary>
/// Component: For managing textures/sprites and spritesheets for the object.
/// </summary>
class SpriteRenderer : public Component
{
public:
	/// <summary>
	/// TODO: SUMMARY
	/// </summary>
	/// <param name="textureTag"></param>
	SpriteRenderer(TextureTag textureTag);
	/// <summary>
	/// TODO: SUMMARY
	/// </summary>
	/// <param name="textureTag"></param>
	/// <param name="currentImage"></param>
	/// <param name="imageCount"></param>
	SpriteRenderer(TextureTag textureTag, Vector2u currentImage, Vector2u imageCount);
	~SpriteRenderer();

	// Inherited via Component
	void Awake() override;
	void Start() override;
	void Update(Time* timePerFrame) override;
	void Destroy() override;
	ComponentTag ToEnum() override;

	/// <summary>
	/// Returns a Sprite
	///  TODO: const
	/// </summary>
	Sprite GetSprite() const;
	/// <summary>
	/// Flips the sprite.
	/// </summary>
	void FlipSprite();
	/// <summary>
	/// Returns the texture.
	///  TODO: const
	/// </summary>
	Texture GetTexture() const;
	// TODO: const
	bool* GetFlipped() const;
	/// <summary>
	/// Returns the textureRect.
	/// </summary>
	/// <returns></returns>
	IntRect GetTextureRect() const;
	/// <summary>
	/// Returns the imageCount.
	/// </summary>
	/// <returns></returns>
	Vector2u GetImageCount() const;

	void SetTextureRect(IntRect textureRect);

private:
	Sprite* sprite;
	Texture* texture;
	bool* flipped;

	IntRect* textureRect;
	Vector2u* currentImage;
	Vector2u* imageCount;
};

#endif