#include "..\Headers\LevelManager.h"


void LevelManager::InstantiateLevel()
{
	Bitmap* level1 = Bitmap::FromFile(L"src/Levels/Level1.bmp");

	Color color;

	level1->GetPixel(0, 0, &color);

	byte b1 = color.GetBlue();
	byte r1 = color.GetRed();
	byte g1 = color.GetGreen();

	byte a = color.GetA();
	byte r = color.GetR();
	byte g = color.GetG();
	byte b = color.GetB();

}