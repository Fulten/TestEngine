#pragma once
// uses bit shifting to combine 4 characters into a single ARGB unsigned integer value

class Color
{
private:
	UINT colorCode;

public:
	Color() : colorCode() {}
	Color(const Color& rhs)
	{
		*this = rhs;
	}
	Color operator=(const Color& rhs)
	{
		colorCode = rhs.colorCode;
	}
	Color(unsigned char a, unsigned char r, unsigned char g, unsigned char b) :
		colorCode( (a << 24u) | (r << 16u) | (g << 8u) | b)	{}

	Color(unsigned char r, unsigned char g, unsigned char b) :
		colorCode ( (r << 16u ) | (g << 8u) | b) {}

	~Color() {}

	void setColorRGB(unsigned char r, unsigned char g, unsigned char b)
	{
		colorCode = ((r << 16u) | (g << 8u) | b);
	}

	const UINT getColor()
	{
		return colorCode;
	}

};

/*
namespace Color
{
	color Red(255, 0, 0);
	color Green(0, 255, 0);
	color Blue(0, 0, 255);
	color Orange(255, 255, 0);
	color Purple(255, 0, 255);
	color Cyan(0, 255, 255);
	color White(255, 255, 255);
	color Black(0, 0, 0);

}*/