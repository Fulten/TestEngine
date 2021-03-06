#include "Map.h"

Map::Map() : width(0),
height(0),
mapTiles(nullptr)
{}

Map::~Map()
{
	if (mapTiles != nullptr) // cleanup
		delete[] mapTiles;
}

// loads a mapFrom a text file
bool Map::getMap(std::string fileName)
{
	// load map based on file name
	std::ifstream mapFile(fileName, std::ios::in, std::ios::binary);
	if (mapFile.fail()) // check that it was opened correctly
		return false;

	mapFile.read((char*)&width, sizeof(width));
	mapFile.read((char*)&height, sizeof(height));

	if (width == 0 || height == 0)
		return false;

	const int size = height * width;

	mapTiles = new Tile[size];
	if (mapTiles == nullptr) // check the memory was correctly allocated
		return false;

	ZeroMemory(mapTiles, sizeof(Tile) * size);

	// load tile values from file
	for (int i = 0; i < size; i++)
		mapFile.read(&mapTiles[i].type, 1);

	mapFile.close();
	return true;
}

// accepts a position and returns the tile at the position 
// returns a tile with type negative if out of bounds or uninitilized
Tile Map::getTile(vec2d<int> pos)
{
	if (mapTiles == nullptr) return Tile(-2);
	if (pos.x > width || pos.x < 0) return Tile(-1);
	if (pos.y > height || pos.y < 0) return Tile(-1);
	return mapTiles[(pos.x + pos.y * width)];
}


Tile Map::getTile(int x, int y)
{
	if (mapTiles == nullptr) return Tile(-2);
	if (x > width || x < 0) return Tile(-1);
	if (y > height || y < 0) return Tile(-1);
	return mapTiles[x + y * width];
}
short Map::getWidth()
{
	return width;
}

short Map::getHeight()
{
	return height;
}

