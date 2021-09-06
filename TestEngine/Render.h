#pragma once
//simple vector based rendering engine
// probably implmented poorly

#include "Win.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "vec2d.h"
#include "DrawCharString.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "Winmm.lib")

// holds positional data relative to the graphics card
struct CUSTOMVERTEX { FLOAT x, y, z, rhw; D3DCOLOR color; };
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

class Render
{
private:
	D3DCOLOR clearColor;
	int triCount, drawSize;
	int windowWidth = 600;
	int windowHeight = 600;
	std::vector<CUSTOMVERTEX> vertices;
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	// vertex buffer thats provided to the graphics card
	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;

protected:
	void build(); // builds a frame for the graphics card
	void send(); // sends a built frame to the graphics card

public:
	Render(HWND& hWnd);
	~Render();

	void dRect(vec2d<> pos, vec2d<> dimensions, D3DCOLOR color);
	void dRectGradiant(vec2d<> pos, vec2d<> dimensions, D3DCOLOR color1, D3DCOLOR color2, char direction);
	void dSqr(vec2d<> pos, short size, D3DCOLOR color);
	void dChar(vec2d<> pos, char ch, short size, D3DCOLOR color);
	void dc_str(vec2d<> pos, const char* ch, short size, D3DCOLOR color);
	void dc_strV(vec2d<> pos, const char* ch, short size, D3DCOLOR color);
	void dVector(vec2d<> pos1, vec2d<> pos2, short size, D3DCOLOR color);
	void setDrawSize(int dSize);
	float getDrawWidth();
	float getDrawHeight();
	void setClearColor(D3DCOLOR color);

};

