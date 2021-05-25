#include "BitmapImage.h"
#include <iostream>
#include <fstream>

BitmapColor::BitmapColor()
	:r(0),g(0),b(0)
{
}

BitmapColor::BitmapColor(float r, float g, float b)
	: r(r), g(g), b(b)
{
}

BitmapColor::~BitmapColor()
{
}

BitmapImage::BitmapImage(int width, int height)
{
	this->width = width;
	this->height = height;
	colors = std::vector<BitmapColor>(width * height);
}

BitmapImage::~BitmapImage()
{
}

BitmapColor BitmapImage::GetColor(int x, int y) const
{
	//Y is the row, and width is the column
	return colors[y * width + x];
}

void BitmapImage::SetColor(const BitmapColor& color, int x, int y)
{
	//Sets the color 
	colors[y * width + x].r = color.r;
	colors[y * width + x].g = color.g;
	colors[y * width + x].b = color.b;
}


//TODO: find ud af hvorfor pointer her
void BitmapImage::Read(const char* path)
{
	std::ifstream f;

	//reading the file in binary
	f.open(path, std::ios::in | std::ios::binary);

	if (!f.is_open())
	{
		std::cout << "File could not be opened" << std::endl;
		return;
	}

	//should be global
	const int fileHeaderSize = 14;
	const int informationHeaderSize = 40;

	unsigned char fileHeader[fileHeaderSize];

	//file header is what it is reading, and the size is the amount it's reading
	f.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);

	if (fileHeader[0] != 'B' || fileHeader[1] != 'M')
	{
		std::cout << "The specified path is not a bitmap";
		f.close();
		return;
	}
	
	unsigned char informationHeader[informationHeaderSize];

	//file header is what it is reading, and the size is the amount it's reading
	f.read(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

	//file size is stored in byte num 2
	//bit shifting 
	//TODO: find ud af hvad bit shifting er, når han ikke gider at snakke om det
	//To combine the 4 byte to an integer.
	int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);

	width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
	height = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);

	colors.resize(width * height);

	const int paddingAmount =((4 - (width * 3) % 4) % 4);

	for (int y = height-1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			unsigned char color[3];
			//load the color
			f.read(reinterpret_cast<char*>(color), 3);

			colors[y * width + x].r = static_cast<float>(color[2]) / 255.0f;
			colors[y * width + x].g = static_cast<float>(color[1]) / 255.0f;
			colors[y * width + x].b = static_cast<float>(color[0]) / 255.0f;
		}
		//skips the padding
		f.ignore(paddingAmount);
	}

	f.close();

	std::cout << "File Read";
}

void BitmapImage::Export(const char* path)
{
	//"filestream"
	std::ofstream f;

	//Writing the file to the path in binary
	f.open(path, std::ios::out | std::ios::binary);

	if (!f.is_open())
	{
		std::cout << "Couldn't open file\n";
		return;
	} 
	
	//Padding for bitmap. Each colorchangel has 3 bytes for storing data.
	//The color array should have a row, which has an amount of memory thats divideable by 4.
	//To make sure that is possible, it needs some padding.
	// look up 8:50 in video for further explanation

	//Can never have more padding than 3
	unsigned char bmpPad[3] = { 0,0,0 };

	//width * 3 is how many bytes the colors have
	// % 4 is how many bytes that its over the correct amount
	//-4 is how many byte that is left that should have padding
	//If its zero % 4
	const int paddingAmount = ((4 - (width * 3) % 4) % 4);

	const int fileHeaderSize = 14;
	const int InformationHeaderSize = 40;

	//the file size based on the amount of color data and padding + headers
	const int fileSize = fileHeaderSize + InformationHeaderSize + width * height * 3 + paddingAmount * height;

	unsigned char fileHeader[fileHeaderSize];

	// File type, first two bytes indicates which file type, Bit, Map
	fileHeader[0] = 'B';
	fileHeader[1] = 'M';

	//TODO: find ud af hvad >> helt præcist gør her
	//File size - split int up into char
	fileHeader[2] = fileSize;
	fileHeader[3] = fileSize >> 8;
	fileHeader[4] = fileSize >> 16;
	fileHeader[5] = fileSize >> 24;

	//Reserved 1 (not used) 
	fileHeader[6] = 0;
	fileHeader[7] = 0;

	//Reserved 2 (not used)
	fileHeader[8] = 0;
	fileHeader[9] = 0;

	//Pixel Data offset; Combined size of headers, which will never exceed 255
	fileHeader[10] = fileHeaderSize + InformationHeaderSize;
	fileHeader[11] = 0;
	fileHeader[12] = 0;
	fileHeader[13] = 0;

	unsigned char informationHeader[InformationHeaderSize];
	//Headersize 
	informationHeader[0] = InformationHeaderSize;
	informationHeader[1] = 0;
	informationHeader[2] = 0;
	informationHeader[3] = 0;

	//image width split up into char
	informationHeader[4] = width;
	informationHeader[5] = width >> 8;
	informationHeader[6] = width >> 16;
	informationHeader[7] = width >> 24;

	//image height split up into char
	informationHeader[8] = height;
	informationHeader[9] = height >> 8;
	informationHeader[10] = height >> 16;
	informationHeader[11] = height >> 24;

	//planes 
	//TODO: find ud af hvad planes er, så der kan skrive en god kommentar
	informationHeader[12] = 1;
	informationHeader[13] = 0;

	//bits per pixel (RGB) color depth
	informationHeader[14] = 24;
	informationHeader[15] = 0;

	//The amount of compression (none this case)
	informationHeader[16] = 0;
	informationHeader[17] = 0;
	informationHeader[18] = 0;
	informationHeader[19] = 0;

	//Image size (no compression this case)
	informationHeader[20] = 0;
	informationHeader[21] = 0;
	informationHeader[22] = 0;
	informationHeader[23] = 0;

	//X pixels per meter (not specified) 
	informationHeader[24] = 0;
	informationHeader[25] = 0;
	informationHeader[26] = 0;
	informationHeader[27] = 0;

	//Y pixels per meter (not specified) 
	informationHeader[28] = 0;
	informationHeader[29] = 0;
	informationHeader[30] = 0;
	informationHeader[31] = 0;

	//Total colors (no coler palette used)
	informationHeader[32] = 0;
	informationHeader[33] = 0;
	informationHeader[34] = 0;
	informationHeader[35] = 0;

	//Important colors (generally ignored)
	informationHeader[36] = 0;
	informationHeader[37] = 0;
	informationHeader[38] = 0;
	informationHeader[39] = 0;

	//write array to the file.
	//Fwrite needs a char pointer, and not unsigned pointer, so it needs to be casted.
	//TODO: hvorfor bruger alle bare unsigned char, er det bare så de slipper for at defininere dem??
	//unsigned char = byte åbenbart.
	f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
	f.write(reinterpret_cast<char*>(informationHeader), InformationHeaderSize);

	//Loop through the pixels
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//multiply it by 255 to make it into the 255 range
			unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * 255.0f);
			unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * 255.0f);
			unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * 255.0f);

			//for some reason bitmaps starts with the blue value
			unsigned char color[] = { b, g, r };

			//TODO: find ud af hvorfor han får stiv dolk over char og casting
			//Writes the color to the file for every pixel
			f.write(reinterpret_cast<char*>(color), 3);
		}

		//for every row it needs padding
		f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
	}

	f.close();

	std::cout << "File created!\n";
}

