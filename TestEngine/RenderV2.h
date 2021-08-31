#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <vector>
#include <string>
#include <assert.h>
#include <system_error>
#include "FultenException.h"
#include "vec2d.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi")

#define GFX_EXCEPTION(message) FultenException(message, __LINE__)

class RenderV2
{
private:
	const UINT m_bufferCount;
	UINT m_displayWidth;
	UINT m_displayHeight;
	D3D_FEATURE_LEVEL FeatureLevels = D3D_FEATURE_LEVEL_11_0;

	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain; // swapchain
	Microsoft::WRL::ComPtr<ID3D11Device> m_dev; // display device
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_devContext; 
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_bufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bufferTextureView;

	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState;




private:

public:
	RenderV2(HWND& hWnd);
	~RenderV2();

	RenderV2() = delete;
	RenderV2(const RenderV2&) = delete;
	RenderV2 operator=(const RenderV2) = delete;

	void build();
	void present();




};

