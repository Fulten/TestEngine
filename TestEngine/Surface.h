#pragma once

#include <fstream>


// stores and adquires texture data
class Surface
{
private:
	int width;
	int height;
	int* pixels = nullptr;


public:
	Surface(std::string fileName);
	~Surface();

	bool GetTexture();
	int getPixel();


};

