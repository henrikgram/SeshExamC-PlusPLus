#ifndef BITMAPCOLOR_H
#define BITMAPCOLOR_H


/*
* The folowing code has been implemented by folowing "Designed by Hugo"'s tutorial on youtube
* https://www.youtube.com/watch?v=vqT5j38bWGg&ab_channel=DesignedbyHugo
*/
#include <vector>

//For the colors of each pixel
struct BitmapColor
{
	float r, g, b;

	BitmapColor();
	BitmapColor(float r, float g, float b);
	~BitmapColor();
};

/// <summary>
/// Class that can read/create bitmaps
/// </summary>
class BitmapImage
{
public:
	/// <summary>
	/// Represents a bitmap image
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	BitmapImage(int width, int height);

	~BitmapImage();

	/// <summary>
	/// Returns a color from a specific position in the image
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	BitmapColor GetColor(int x, int y) const;

	/// <summary>
	/// Changes the color of a pixel
	/// </summary>
	/// <param name="color">Which color</param>
	/// <param name="x">Position X</param>
	/// <param name="y">position Y</param>
	void SetColor(const BitmapColor& color, int x, int y);

	/// <summary>
	/// Reads a BMP image file
	/// </summary>
	/// <param name="path">The specified path, has to be const char * because of ifstream</param>
	void Read(const char* path);

	/// <summary>
	/// Exports the bitmap image to the path
	/// </summary>
	/// <param name="path"></param>
	void Export(const char* path);

	int GetHeight() const;
	int GetWidth() const;

private:
	int width;
	int height;
	std::vector<BitmapColor> colors;
};

#endif