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
	/// Constructor for SpriteRenderer.
	/// Takes a texture tag so it knows which texture the object uses/needs.
	/// </summary>
	/// <param name="textureTag"> The asset the object uses/needs </param>
	SpriteRenderer(TextureTag textureTag);

	/// <summary>
	/// For managing textures/sprites and spritesheets for the object.
	/// </summary>
	/// <param name="textureTag">What texture(spritesheet) the sprite will load from the asset class</param>
	/// <param name="currentImage">Which image position will be the current image</param>
	/// <param name="imageCount">How many images and rows the spritesheet has</param>
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
	/// </summary>
	Sprite GetSprite() const;
	/// <summary>
	/// Flips the sprite.
	/// </summary>
	void FlipSprite();
	/// <summary>
	/// Returns the texture.
	/// </summary>
	Texture GetTexture() const;

	bool GetFlipped() const;
	void SetFlipped(bool newValue);
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