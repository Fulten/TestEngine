#include "RenderV2.h"

#define GFX_EXCEPTION(hr) throw FultenException::FultenException(hr, __LINE__, __FILE__)
#define FULTEN_EXCEPTION(desc) throw FultenException::FultenException(desc, __LINE__, __FILE__) 

namespace wrl = Microsoft::WRL;

// constructor
RenderV2::RenderV2(HWND hWnd, FULTEN_DISPLAY_DESC displayDesc)
	: displayDesc(displayDesc)
{
	InitlizeD3D(hWnd);
}

// destructor
RenderV2::~RenderV2()
{
	this->CleanD3D();
}

// initlize our direct 3d devices
bool RenderV2::InitlizeD3D(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferDesc.Width = displayDesc.nScreenWidth;
	scd.BufferDesc.Height = displayDesc.nScreenHeight;
	scd.BufferDesc.Format = displayDesc.fColorFormat;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hWnd;
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = 0;

	HRESULT hr;

	// initilize direct3d device and swapchain
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&pSwap,
		&pDev,
		nullptr,
		&pDevContext)))
		GFX_EXCEPTION(hr);

	InitilizeVertexShader();
	InitilizePixelShader();


	return true;
}

// release created objects
void RenderV2::CleanD3D()
{
}

// reads the vertex shader from a cso file and binds it to the rendering pipline
void RenderV2::InitilizeVertexShader()
{
	HRESULT hr; // debiug value


	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	// read and create shader from file data
	std::vector<BYTE> shaderFile = LoadShaderFromFile("2DVertexTestShader.cso");
	if (FAILED(hr = pDev->CreateVertexShader(shaderFile.data(),
		shaderFile.size(),
		nullptr,
		pVertexShader.GetAddressOf())))
		GFX_EXCEPTION(hr);

	// bind vertex shader to the pipeline
	pDevContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	// com pointer containing the input layout for our shaders
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;

	// array of structs used to define input layout
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION2D", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// binds our defined input layout to the rendering pipeline
	if (FAILED(hr = pDev->CreateInputLayout(
		ied,
		2u,
		shaderFile.data(),
		shaderFile.size(),
		&pInputLayout)))
		GFX_EXCEPTION(hr);

	pDevContext->IASetInputLayout(pInputLayout.Get());

}

// reads the pixel shader from a cso file and binds it to the rendering pipline
void RenderV2::InitilizePixelShader()
{
	HRESULT hr; // debiug value

	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	// read and create shader from file data
	std::vector<BYTE> shaderFIle = LoadShaderFromFile("PixelTestShader.cso");
	if (FAILED(hr = pDev->CreatePixelShader(shaderFIle.data(),
		shaderFIle.size(),
		nullptr,
		pPixelShader.GetAddressOf())))
		GFX_EXCEPTION(hr);

	// bind pixel shader to the pipeline
	pDevContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}

// wipes background of screen buffer to given color (colors should unorm)
void RenderV2::ClearBackground(float red, float green, float blue)
{
	HRESULT hr;

	wrl::ComPtr<ID3D11Resource> pBackBuffer;

	if (FAILED(hr = pSwap->GetBuffer(0,
		__uuidof(ID3D11Resource),
		&pBackBuffer)))
		GFX_EXCEPTION(hr);


	if (FAILED(hr = pDev->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&pRenderTarget)))
		GFX_EXCEPTION(hr);

	FLOAT color[4] = { red, green, blue, 1.0 };

	pDevContext->ClearRenderTargetView(
		pRenderTarget.Get(),
		color);
}

// returns the width of the screen in pixels
int RenderV2::getScreenWidth()
{
	return displayDesc.nScreenWidth;
}

// returns the height of the screen in pixels
int RenderV2::getScreenHeight()
{
	return displayDesc.nScreenHeight;
}

void RenderV2::DrawTestTriangle()
{
	const Vertex vertices[] =
	{
		{ 0.0f,  0.5f, 1.0f, 0.0f, 0.0f},
		{ 0.5f, -0.5f, 0.0f, 1.0f, 0.0f},
		{-0.5f, -0.5f, 0.0f, 0.0f, 1.0f}

	};

	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC pd;
	pd.Usage = D3D11_USAGE_DEFAULT;
	pd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	pd.CPUAccessFlags = 0u;
	pd.MiscFlags = 0u;
	pd.StructureByteStride = sizeof(Vertex);
	pd.ByteWidth = sizeof(vertices);

	D3D11_SUBRESOURCE_DATA psd;
	psd.pSysMem = vertices;

	HRESULT hr;

	if (FAILED(hr = pDev->CreateBuffer(
		&pd,
		&psd,
		&pVertexBuffer)))
		GFX_EXCEPTION(hr);

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;

	pDevContext->IASetVertexBuffers(
		0u,
		1u,
		pVertexBuffer.GetAddressOf(),
		&stride,
		&offset);

	// bind render target
	pDevContext->OMSetRenderTargets(1u, pRenderTarget.GetAddressOf(), nullptr);

	// set primitive topology
	pDevContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// describe the viewport we are using
	D3D11_VIEWPORT vp;
	vp.Width = (float)displayDesc.nScreenWidth;
	vp.Height = (float)displayDesc.nScreenHeight;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	// configuring the bound viewport
	pDevContext->RSSetViewports(1u, &vp);

	pDevContext->Draw(3u, 0u);
}

// present frame from backbuffer
void RenderV2::PresentFrame()
{
	pSwap->Present(1u, 0u);
}

// reads a file into memory as an array of bytes using the filename
std::vector<BYTE> RenderV2::LoadShaderFromFile(std::string fileName)
{
	// open file
	std::ifstream file(fileName, std::ios::in | std::ios::binary);

	if (file.fail())
		FULTEN_EXCEPTION(("Error opening shaderFile: " + fileName).c_str());

	file.seekg(0, std::ios::end);
	int length = file.tellg();
	file.seekg(0, std::ios::beg);
	file.clear();

	std::vector<BYTE> fileData(length);

	file.read((char*)fileData.data(), length);
	file.close();

	return fileData;
}