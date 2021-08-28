#pragma once
// converts a character into a string of characters 
// charcters produced are 5 x 7


#include <string>

static void characterDrawString(char* buff, char ch)
{
	if (ch >= 97 && ch <= 122)
		ch -= 32;

	std::string toDraw = "";

	switch (ch)
	{
	case 'A':
		toDraw =  "..###..";
		toDraw += ".#...#.";
		toDraw += ".#####.";
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		break;

	case 'B':
		toDraw += "..###..";
		toDraw += ".#...#.";
		toDraw += ".####..";
		toDraw += ".#...#.";
		toDraw += ".####..";
		break;

	case 'C':
		toDraw += "..####.";
		toDraw += ".#.....";
		toDraw += ".#.....";
		toDraw += ".#.....";
		toDraw += "..####.";
		break;

	case 'D':
		toDraw += ".####..";
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		toDraw += ".####..";
		break;

	case 'E':
		toDraw += "..###..";
		toDraw += ".#.....";
		toDraw += ".###...";
		toDraw += ".#.....";
		toDraw += "..###..";
		break;

	case 'F':
		toDraw += "..####.";
		toDraw += ".#.....";
		toDraw += ".####..";
		toDraw += ".#.....";
		toDraw += ".#.....";
		break;

	case 'G':
		toDraw += "..###..";
		toDraw += ".#.....";
		toDraw += ".#..##.";
		toDraw += ".#...#.";
		toDraw += "..###..";
		break;

	case 'H':
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		toDraw += ".#####.";
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		break;

	case 'I':
		toDraw += ".#####.";
		toDraw += "...#...";
		toDraw += "...#...";
		toDraw += "...#...";
		toDraw += ".#####.";
		break;

	case 'J':
		toDraw += "..####.";
		toDraw += ".....#.";
		toDraw += ".....#.";
		toDraw += ".#...#.";
		toDraw += "..###..";
		break;

	case 'K':
		toDraw += ".#...#.";
		toDraw += ".#..#..";
		toDraw += ".###...";
		toDraw += ".#..#..";
		toDraw += ".#...#.";
		break;

	case 'L':
		toDraw += ".#.....";
		toDraw += ".#.....";
		toDraw += ".#.....";
		toDraw += ".#.....";
		toDraw += "..####.";
		break;

	case 'M':
		toDraw += ".#...#.";
		toDraw += ".##.##.";
		toDraw += ".#.#.#.";
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		break;

	case 'N':
		toDraw += ".#...#.";
		toDraw += ".##..#.";
		toDraw += ".#.#.#.";
		toDraw += ".#..##.";
		toDraw += ".#...#.";
		break;

	case 'O':
		toDraw += "..###..";
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		toDraw += "..###..";
		break;

	case 'P':
		toDraw += "..###..";
		toDraw += ".#...#.";
		toDraw += ".####..";
		toDraw += ".#.....";
		toDraw += ".#.....";
		break;

	case 'Q':
		toDraw += "..###..";
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		toDraw += ".#.#.#.";
		toDraw += "..#.##.";
		break;

	case 'R':
		toDraw += "..###..";
		toDraw += ".#...#.";
		toDraw += ".####..";
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		break;

	case 'S':
		toDraw += "..####.";
		toDraw += ".#.....";
		toDraw += "..###..";
		toDraw += ".....#.";
		toDraw += ".####..";
		break;

	case 'T':
	{
		toDraw += ".#####.";
		toDraw += "...#...";
		toDraw += "...#...";
		toDraw += "...#...";
		toDraw += "...#...";
	}

	break;

	case 'U':
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		toDraw += "..###..";
		break;

	case 'V':
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		toDraw += "..#.#..";
		toDraw += "..#.#..";
		toDraw += "...#...";
		break;

	case 'W':
		toDraw += ".#...#.";
		toDraw += ".#...#.";
		toDraw += ".#.#.#.";
		toDraw += ".#####.";
		toDraw += "..#.#..";
		break;

	case 'X':
		toDraw += ".#...#.";
		toDraw += "..#.#..";
		toDraw += "...#...";
		toDraw += "..#.#..";
		toDraw += ".#...#.";
		break;

	case 'Y':
		toDraw += ".#...#.";
		toDraw += "..#.#..";
		toDraw += "...#...";
		toDraw += "...#...";
		toDraw += "...#...";
		break;

	case 'Z':
		toDraw += ".#####.";
		toDraw += "....#..";
		toDraw += "...#...";
		toDraw += "..#....";
		toDraw += ".#####.";
		break;

	case ' ':
		toDraw += ".......";
		toDraw += ".......";
		toDraw += ".......";
		toDraw += ".......";
		toDraw += ".......";
		break;

	case ':':
		toDraw += ".#.....";
		toDraw += ".#.....";
		toDraw += ".......";
		toDraw += ".#.....";
		toDraw += ".#.....";
		break;

	case '.':
		toDraw += ".......";
		toDraw += ".......";
		toDraw += ".......";
		toDraw += "..##...";
		toDraw += "..##...";
		break;

	case '1':
		toDraw += "...#...";
		toDraw += "..##...";
		toDraw += "...#...";
		toDraw += "...#...";
		toDraw += "..###..";
		break;

	case '2':
		toDraw += "..###..";
		toDraw += ".#...#.";
		toDraw += "....#..";
		toDraw += "...#...";
		toDraw += ".#####.";
		break;

	case '3':
		toDraw += ".####..";
		toDraw += ".....#.";
		toDraw += "...##..";
		toDraw += ".....#.";
		toDraw += ".####..";
		break;

	case '4':
		toDraw += "...##..";
		toDraw += "..#.#..";
		toDraw += ".#..#..";
		toDraw += ".#####.";
		toDraw += "....#..";
		break;

	case '5':
		toDraw += ".#####.";
		toDraw += ".#.....";
		toDraw += ".####..";
		toDraw += ".....#.";
		toDraw += ".####..";
		break;

	case '6':
		toDraw += "..###..";
		toDraw += ".#.....";
		toDraw += ".####..";
		toDraw += ".#...#.";
		toDraw += "..###..";
		break;

	case '7':
		toDraw += ".#####.";
		toDraw += ".....#.";
		toDraw += "....#..";
		toDraw += "...#...";
		toDraw += "..#....";
		break;

	case '8':
		toDraw += "..###..";
		toDraw += ".#...#.";
		toDraw += "..###..";
		toDraw += ".#...#.";
		toDraw += "..###..";
		break;

	case '9':
		toDraw += "..###..";
		toDraw += ".#...#.";
		toDraw += "..####.";
		toDraw += ".....#.";
		toDraw += "..###..";
		break;

	case '0':
		toDraw += "..###..";
		toDraw += ".##..#.";
		toDraw += ".#.#.#.";
		toDraw += ".#..##.";
		toDraw += "..###..";
		break;

	case '-':
		toDraw += ".......";
		toDraw += ".......";
		toDraw += "#######";
		toDraw += ".......";
		toDraw += ".......";
		break;

	default:
		toDraw += "#######";
		toDraw += "#.#.#.#";
		toDraw += "#..#..#";
		toDraw += "#.#.#.#";
		toDraw += "#######";
		break;
	}

	for (short i = 0; i < 36; i++)
	{
		*buff = toDraw[i];
		buff++;
	}
}