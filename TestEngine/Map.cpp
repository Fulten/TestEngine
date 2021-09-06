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

// loads a map from a text file of given name
bool Map::getMap(std::string fileName)
{
	// load map based on fileName
	std::ifstream mapFile (fileName, std::ios::in | std::ios::binary);
	if (mapFile.fail()) // check that it was opened correctly
		return false;

	mapFile.read((char*)&width, sizeof(width));
	mapFile.read((char*)&height, sizeof(height));
	
	if (width == 0 || height == 0)
		return false;

	const int size = height * width;

	mapTiles = new Tile[size] { 0 };
	if (mapTiles == nullptr) // check the memory was correctly allocated
		return false;

	
	// load tile values from file
	for (int i = 0; i < size; i++)
		mapFile.read(&mapTiles[i].type, 1);

	mapFile.close();
	return true;
}

// wrapper that accepts a vector
Tile Map::getTile(vec2d<int> pos)
{
	return getTile(pos.x, pos.y);
}

// accepts two integers and returns a tile at the corrasponding position
// returns a tile with type negative if out of bounds or uninitilized
Tile Map::getTile(int x, int y)
{
	if (x > width || x < 0) return Tile(-1);
	if (y > height || y < 0) return Tile(-1);
	return mapTiles[x + y * width];
}

// returns map width
short Map::getWidth()
{
	return width;
}

// returns map height
short Map::getHeight()
{
	return height;
}

