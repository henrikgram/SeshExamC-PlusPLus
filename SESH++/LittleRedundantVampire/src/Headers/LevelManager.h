#pragma once
#include <iostream>
#include "BitmapImage.h"
#include "GameObject.h"
#include "../Enum/TextureTag.h"
#include "Components/SpriteRenderer.h"
//#include <Windows.h>
//#include <ObjIdl.h>
//#include <gdiplus.h>
//#include <string>
//
//#pragma comment (lib,"Gdiplus.lib")
//
//using namespace std;
//
//using namespace Gdiplus;

class LevelManager
{
private:
	//Bitmap* level;

public:
	vector<GameObject*>* InstantiateLevel();

	       // // Retrieve the image.
        //image1 = new Bitmap(@"C:\Documents and Settings\All Users\" 
        //    + @"Documents\My Music\music.bmp", true);

};

