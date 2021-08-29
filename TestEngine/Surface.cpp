#include "Surface.h"


Surface::Surface(std::string fileName)
{
	std::ifstream(fileName, std::ios::in, std::ios::binary);


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
