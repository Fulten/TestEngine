#include "Render.h"

Render::Render(HWND& hWnd)
	: triCount(0), drawSize(1)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	// set the width and hieght in pixels of the render target
	d3dpp.BackBufferWidth = windowWidth;
	d3dpp.BackBufferHeight = windowHeight;

	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);
}

Render::~Render()
{
	if(v_buffer != NULL)
		v_buffer->Release();
	d3ddev->Release();
	d3d->Release();
}

// builds a frame for the graphics card
void Render::Build()
{
	// get a chunk of memory to write vertices to
	d3ddev->CreateVertexBuffer(vertices.size() * sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);

	// void pointer used to send data to the graphics card
	VOID* pVoid;

	// adjust the alignment of vertices to line up with pixels
	auto iter = vertices.begin();
	for (; iter < vertices.end(); iter++)
	{
		iter->x -= 0.5;
		iter->x *= drawSize;
		iter->y -= 0.5;
		iter->y *= drawSize;
	}

	// freeze the vertex buffer while we are managing it
	v_buffer->Lock(0,0, (void**)&pVoid, 0);
	// copy memory from vertices into the buffer
	memcpy(pVoid, vertices.data(), vertices.size() * sizeof(CUSTOMVERTEX));
	v_buffer->Unlock(); // unlock the buffer now that we are done

	//empty out vertices 
	vertices.clear();
}

// sends a built frame to the graphics card
void Render::Send()
{
	// clear previous frame
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->BeginScene();

	d3ddev->SetFVF(CUSTOMFVF);
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
	for (int i = 0; i < triCount / 2; i++)
		d3ddev->DrawPrimitive(D3DPT_TRIANGLEFAN, i * 4, 2);

	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);
	v_buffer->Release();

	triCount = 0;
}

// draws a square to the screen
void Render::dSqr(vec2d<> pos, short size, D3DCOLOR color)
{
	vertices.push_back({ pos.x			, pos.y			, 0.5f, 1.0f, color, });
	vertices.push_back({ pos.x + size	, pos.y			, 0.5f, 1.0f, color, });
	vertices.push_back({ pos.x + size	, pos.y + size	, 0.5f, 1.0f, color, });
	triCount += 1;
	vertices.push_back({ pos.x			, pos.y + size	, 0.5f, 1.0f, color, });
	triCount += 1;
}

// draws a rectangle to the screen
void Render::dRect(vec2d<> pos, vec2d<float> dimensions, D3DCOLOR color)
{
	vertices.push_back({ pos.x					, pos.y					, 0.5f, 1.0f, color, });
	vertices.push_back({ pos.x + dimensions.x	, pos.y					, 0.5f, 1.0f, color, });
	vertices.push_back({ pos.x + dimensions.x	, pos.y + dimensions.y	, 0.5f, 1.0f, color, });
	triCount += 1;
	vertices.push_back({ pos.x					, pos.y + dimensions.y	, 0.5f, 1.0f, color, });
	triCount += 1;
}

// draws a rectangle to the screen with a gradient from one color to another
void Render::dRectGradiant(vec2d<> pos, vec2d<> dimensions, D3DCOLOR color1, D3DCOLOR color2, char direction)
{
	D3DCOLOR c[4];
	ZeroMemory(c, sizeof(*c) * 4);

	direction %= 3;
	c[direction] = color1;
	direction %= 3;
	c[direction+1] = color1;
	direction %= 3;
	c[direction+2] = color2;
	direction %= 3;
	c[direction+3] = color2;
									
	vertices.push_back({ pos.x					, pos.y					, 0.5f, 1.0f, c[0], });
	vertices.push_back({ pos.x + dimensions.x	, pos.y					, 0.5f, 1.0f, c[1], });
	vertices.push_back({ pos.x + dimensions.x	, pos.y + dimensions.y	, 0.5f, 1.0f, c[2], });
	triCount += 1;																	   
	vertices.push_back({ pos.x					, pos.y + dimensions.y	, 0.5f, 1.0f, c[3], });
	triCount += 1;
}

// draws a single character to the screen
void Render::dChar(vec2d<> pos, char ch, short size, D3DCOLOR color)
{
	char toDraw[36] = { 0 };
	characterDrawString(toDraw, ch);

	for (int x = 0; x < 7; x++)
		for (int y = 0; y < 5; y++)
			if (toDraw[x + y * 7] == '#')
				dSqr(pos + vec2d<float>(x * size, y * size), size, color);

}

// draws a string of characters to the screen
void Render::dc_str(vec2d<> pos, const char* ch, short size, D3DCOLOR color)
{
	for (int i = 0; *ch != 0; ch++, i++)
		dChar(pos + vec2d<>(i * size * 7, 0), *ch, size, color);
}

// draws a string of characters to the screen oriented vertically
void Render::dc_strV(vec2d<> pos, const char* ch, short size, D3DCOLOR color)
{
	for (int i = 0; *ch != 0; ch++, i++)
		dChar(pos + vec2d<>(0, i * size * 6), *ch, size, color);
}

// draws a line between two points
void Render::dVector(vec2d<> pos1, vec2d<> pos2, short size, D3DCOLOR color)
{
	vec2d<> dxy = pos2 - pos1;
	vec2d<> xy;
	float lengthSq = dxy.getLengthSq();
	dxy.normalize();

	for (; xy.getLengthSq() < lengthSq;)
	{
		dSqr(pos1 + xy * size, size, color);
		xy += dxy;
	}
}

// sets drawSize a value used to scale size of all primitives drawn to screen
void Render::setDrawSize(int dSize)
{
	if (dSize > 0 && dSize < 100);
		drawSize = dSize;
}

// returns the width the the draw area of the window relative to drawSize
float Render::getDrawWidth()
{
	return windowWidth / drawSize;
}

// returns the height the the draw area of the window relative to drawSize
float Render::getDrawHeight()
{
	return windowHeight / drawSize;
}

// sets the color the frame is cleared to before drawing the next frame
void Render::setClearColor(D3DCOLOR color)
{
	clearColor = color;
}