#pragma once
// enumorator for common colors in the D3DCOLOR format

#include <d3d9.h>

namespace Color
{
	enum color
	{
		RED			= D3DCOLOR_XRGB(255, 0, 0),
		RED_LIGHT	= D3DCOLOR_XRGB(255, 100, 100),
		GREEN		= D3DCOLOR_XRGB(0, 255, 0),
		GREEN_LIGHT = D3DCOLOR_XRGB(100, 255, 100),
		BLUE		= D3DCOLOR_XRGB(0, 0, 255),
		BLUE_LIGHT	= D3DCOLOR_XRGB(100, 100, 255),
		PURPLE		= D3DCOLOR_XRGB(255, 0, 255),
		ORANGE		= D3DCOLOR_XRGB(255, 255, 0),
		CYAN		= D3DCOLOR_XRGB(0, 255, 255),
		BLACK		= D3DCOLOR_XRGB(0, 0, 0),
		GREY		= D3DCOLOR_XRGB(150, 150, 150),
		WHITE		= D3DCOLOR_XRGB(255, 255, 255)

	};
}