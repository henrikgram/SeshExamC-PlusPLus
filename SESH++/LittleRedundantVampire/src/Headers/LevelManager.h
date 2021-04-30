#pragma once
#include <iostream>
#include <Windows.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#include <string>

#pragma comment (lib,"Gdiplus.lib")

using namespace std;

using namespace Gdiplus;

class LevelManager
{
private:
	Bitmap* level;

public:
	void InstantiateLevel();

	       // // Retrieve the image.
        //image1 = new Bitmap(@"C:\Documents and Settings\All Users\" 
        //    + @"Documents\My Music\music.bmp", true);

};

