#pragma once

#include "Win.h"
#include <wrl.h>
#include <d3d11.h>
#include <vector>
#include <string>
#include <assert.h>
#include <fstream>

#include "FultenException.h"
#include "Color.h"

#pragma comment (lib, "d3d11.lib")

#define GFX_EXCEPTION(message) FultenException(message, __LINE__, __FILE__)
#define GFX_EXCEPTION_EXTENDED(message, desc) FultenException(message, __LINE__, __FILE__, desc)


class RenderV2
{
private:

	#include "Texture2D.h"

	const UINT m_bufferCount;

	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain; //
	Microsoft::WRL::ComPtr<ID3D11Device> m_dev; // display device
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_devContext; //
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView; //
	
	
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_Texture; //
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TextureView; //

	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader; //
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader; //
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer; //

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout; //
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState; //
	

	struct Vertex2DTextured
	{
		FLOAT X, Y; // position
		FLOAT tu, tv; // texture mapping
	};

protected:
	UINT m_displayWidth;
	UINT m_displayHeight;

private:
	std::vector<char> LoadShaderFromFile(std::string fileName);
	std::vector<pixel> LoadTextureFromFile(std::string fileName);
	float clearColor[4] = { 0, 0, 0, 1.0 };

	std::vector<Vertex2DTextured> vertices; //
	std::vector<pixel> pixels;

public:
	RenderV2(HWND hWnd);
	~RenderV2();
	RenderV2() = delete;
	RenderV2(const RenderV2&) = delete;
	RenderV2 operator=(const RenderV2) = delete;

	void build();
	void present();
	void setClearColor(unsigned char r, unsigned char g, unsigned char b);
	void setClearColorf(float r, float g, float b, float a);

	
	int getDisplayX();
	int getDisplayY();

	void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);

};

