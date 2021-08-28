// MapEditor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include "Map.h"

using namespace std;

void writeMap();
void readMap();

int main()
{
	cout << "Loading Map Editor...\n";
	writeMap();

	
}

void readMap()
{
	Map map;
	map.getMap("map.txt");
	string test = "";
	for (int i = 0; i < map.getWidth() * map.getHeight(); i++)
	{
		
	}



	cout << "Done\n";
}

void writeMap()
{
	short width = 32, height = 16;

	string mapout = "";
	mapout += "##.####################....#####";
	mapout += "#.......##..###.......#....#####";
	mapout += "#..2.2..##..###..####.##..######";
	mapout += "#..................##..........#";
	mapout += "#..2.2.....####.####..#.....11.1";
	mapout += "#..........#.......#..#.....1..1";
	mapout += "#1111.11111#.......#..#...111..1";
	mapout += "#.....................#...111111";
	mapout += "#.###.22..##.......#..#....1...#";
	mapout += "#.###.22...#.......#..#...11....";
	mapout += "#..#..22...####.####..#........#";
	mapout += "#..#..................#.####.###";
	mapout += "#..#..1111111111...#####...#...#";
	mapout += "#..#..11...11111...#...#.3.###.#";
	mapout += "#......................#.......#";
	mapout += "###..###########################";

	// open file for writing
	ofstream mapFile("map.txt",  ios::out, ios::binary);
	if (mapFile.fail()) // check that it was opened
	{
		cout << "failed to open output file.\n";
	}

	cout << "writing map data...\n";

	mapFile.write((char*)&width, sizeof(width));
	mapFile.write((char*)&height, sizeof(height));

	mapFile.write(mapout.data(), mapout.size());


	cout << "Done.\n";
	mapFile.close();
}
