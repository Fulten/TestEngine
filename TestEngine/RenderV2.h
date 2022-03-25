#pragma once

#define NOMINMAX

#include <Windows.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <d3d11.h>
#include <d3dx11.h>
#include <wrl.h>

#include "FultenException.h"


// direct 3d libraries
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")

class RenderV2
{
public:
	struct FULTEN_DISPLAY_DESC
	{
		int nScreenWidth;
		int nScreenHeight;
		DXGI_FORMAT fColorFormat;
	};

private:
	// used to store information about display configuration
	FULTEN_DISPLAY_DESC displayDesc;

	struct Vertex
	{
		float x, y;
		float r, g, b;
	};

	// pointers used to contain direct3d devices
	// pSwap contains the interface to the swapchain
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	// pDev is used primaraly to create other devices
	Microsoft::WRL::ComPtr<ID3D11Device> pDev;
	// pDevContext is used to interface with the rendering pipeline
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDevContext;
	// pRenderTarget allows us to set what need to be rendered
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTarget;

	bool InitlizeD3D(HWND hWnd); // initilizes direct3d devices
	void CleanD3D(); // cleans up our registered devices
	void InitilizeVertexShader(); // initilizes the vertex shader
	void InitilizePixelShader(); // initilizes the pixel shader

	// reads a given file into memory as an array of characters
	std::vector<BYTE> LoadShaderFromFile(std::string fileName);

public:
	RenderV2(HWND hWnd, FULTEN_DISPLAY_DESC displayDesc); // constructor
	RenderV2(const RenderV2&) = delete; // copy constructor is deleted
	RenderV2() = delete;
	RenderV2& operator=(const RenderV2&) = delete; // assignment operator is deleted
	~RenderV2(); // destructor

	void PresentFrame();
	void ClearBackground(float red, float green, float blue);
	void DrawTestTriangle();
	int getScreenWidth();
	int getScreenHeight();

};