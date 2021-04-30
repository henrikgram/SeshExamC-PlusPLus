#include "..\Headers\LevelManager.h"


void LevelManager::InstantiateLevel()
{
	//wstring path = L"C:\Users\Henrik\Documents\GitHub\SeshExamC-PlusPLus\SESH++\LittleRedundantVampire\src\Levels\Level1.bmp";
	//LevelManager::level->FromFile(path.c_str(), true);

	//Bitmap bm(L"/Levels/pik.bmp");

	Color pixelColor;

	level->GetPixel(1, 1, &pixelColor);

	byte a = pixelColor.GetA();
	byte r = pixelColor.GetR();
	byte g = pixelColor.GetG();
	byte b = pixelColor.GetB();

	pixelColor.MakeARGB(a, r, g, b);
	
	cout << pixelColor.GetGreen();

	//cout << pixelColor << endl;
}