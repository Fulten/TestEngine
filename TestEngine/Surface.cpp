#include "Surface.h"


Surface::Surface(std::string fileName)
{
	std::ifstream fileIn(fileName, std::ios::in, std::ios::binary);

	fileIn.close();
}

Surface::~Surface()
{
	if (pixels != nullptr)
		delete[] pixels;

	pixels = nullptr;
}

bool Surface::GetTexture()
{

	return false;
}

int Surface::getPixel()
{

	return 0;
}
