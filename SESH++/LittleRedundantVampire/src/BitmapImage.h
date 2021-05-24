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
/// TODO: is this correct?
/// For creating bitmaps.
/// </summary>
class BitmapImage
{
public:
	BitmapImage(int width, int height);
	~BitmapImage();

	BitmapColor GetColor(int x, int y) const;
	void SetColor(const BitmapColor& color, int x, int y);

	void Read(const char* path);

	void Export(const char* path);

//TODO: make constant
	int GetHeight();
	int GetWidth();

private:
	int width;
	int height;
	std::vector<BitmapColor> colors;
};

#endif