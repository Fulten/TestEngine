#pragma once
// class can read a text file containing binary data 
// and convert it into an array of tiles that can be accessed

#include "vec2d.h"
#include <string>
#include <fstream>
#include <windows.h>

// represents one tile on the map
struct Tile
{
	char type;
	Tile() : type(0)
	{}

	Tile(char type_in) : type(type_in)
	{}
};

// represents a level map
class Map
{
private:
	short width;
	short height;
	Tile* mapTiles;
	
public:
	Map();
	~Map();

	bool getMap(std::string fileName);
	Tile getTile(vec2d<int> pos);
	Tile getTile(int x, int y);
	short getWidth();
	short getHeight();


};

