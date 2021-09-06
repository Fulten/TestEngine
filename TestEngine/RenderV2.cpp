#include "RenderV2.h"

RenderV2::RenderV2(HWND hWnd) :
	m_bufferCount(1)
{
	// define display sepcifications
	m_displayHeight = 600;
	m_displayWidth = 600;
	setClearColor(0, 0, 0);

	/*pixels.reserve(m_displayHeight * m_displayWidth);

	for (int i = 0; i < pixels.capacity(); i++)
	{
		pixels.push_back({ 0 });
	}*/

	// load in shaders to be used from file
	std::vector<char> s_2DVertexShader = LoadShaderFromFile("2DVertexTestShader.cso");
	std::vector<char> s_PixelShader = LoadShaderFromFile("PixelTestShader.cso");
	//std::vector<char> s_PixelShader = LoadShaderFromFile("UVMAPPixelShader.cso");

	Texture2D testTexture("TestGraphics.bmp");

	DXGI_FORMAT Colorformat = DXGI_FORMAT_R8G8B8A8_UNORM;
	D3D_FEATURE_LEVEL FeatureLevels = D3D_FEATURE_LEVEL_11_0;

	// describe the swap chain
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = m_displayWidth;   // Render Resolution size
	sd.BufferDesc.Height = m_displayHeight; // 600 x 600
	sd.BufferDesc.RefreshRate.Numerator = 60; // 60 fps
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = Colorformat;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1; // leave super sampleing disabled
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	sd.BufferCount = m_bufferCount; // double buffering
	sd.OutputWindow = hWnd; // display to the applications window
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	HRESULT hr; // store hresult value for debugging output

	// create directx11 device and swapchain
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		&FeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&m_SwapChain,
		&m_dev,
		NULL,
		&m_devContext)))
		throw GFX_EXCEPTION(hr);
	
	// create a handel to one of the swapchains back buffers
	Microsoft::WRL::ComPtr<ID3D11Resource> b_backBuffer;
	// get back buffer to set as render target view
	if (FAILED(hr = m_SwapChain->GetBuffer(
		0,
		IID_PPV_ARGS(&b_backBuffer))))
		throw GFX_EXCEPTION(hr);

	// assign render target view
	if (FAILED(hr = m_dev->CreateRenderTargetView(
		b_backBuffer.Get(),
		nullptr,
		m_RenderTargetView.GetAddressOf())))
		throw GFX_EXCEPTION(hr);

	// configure viewport
	D3D11_VIEWPORT vp = {};
	vp.Width = m_displayWidth;
	vp.Height = m_displayHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;

	m_devContext->RSSetViewports(1, &vp); // set viewport
	m_devContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // select primitve

	// create a vertex shader using .cso and assign it to com object
	if(FAILED(hr = m_dev->CreateVertexShader(
		s_2DVertexShader.data(),
		s_2DVertexShader.size(),
		nullptr,
		&m_vertexShader)))
		throw GFX_EXCEPTION(hr);

	// setting created shader as vertex shader
	m_devContext->VSSetShader(
		m_vertexShader.Get(),
		nullptr,
		0);

	// create pixel shader using .cso and assign it to com object
	if (FAILED(hr = m_dev->CreatePixelShader(
		s_PixelShader.data(),
		s_PixelShader.size(),
		nullptr,
		&m_pixelShader)))
		throw GFX_EXCEPTION(hr);

	// set set shader as pixel shader
	m_devContext->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0);

	D3D11_INPUT_ELEMENT_DESC layoutd[] =
	{
		{"POSITION2D", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// create an input layout
	m_dev->CreateInputLayout(
		layoutd,
		2,
		s_2DVertexShader.data(),
		s_2DVertexShader.size(),
		m_inputLayout.GetAddressOf());
	
	m_devContext->IASetInputLayout(m_inputLayout.Get());
	// set render target
	m_devContext->OMSetRenderTargets(
		1,
		m_RenderTargetView.GetAddressOf(),
		nullptr);

	if (testTexture.wasCreated())
		if (FAILED(hr = testTexture.makeIntoDXGITex(m_dev, m_Texture)))
			throw GFX_EXCEPTION(hr);

	// describe the resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC rvdesc = {};
	rvdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rvdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	rvdesc.Texture2D.MipLevels = 1;
	rvdesc.Texture2D.MostDetailedMip = 0;

	// get shader resource view
	if (FAILED(hr = m_dev->CreateShaderResourceView(
		m_Texture.Get(),
		&rvdesc,
		&m_TextureView)))
		throw GFX_EXCEPTION(hr);

	// set shader resource view 
	m_devContext->PSSetShaderResources(0,
		1,
		m_TextureView.GetAddressOf());

	D3D11_SAMPLER_DESC sampled = {};
	sampled.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampled.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampled.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampled.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampled.MipLODBias = 0;
	sampled.MaxAnisotropy = 1;
	sampled.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampled.BorderColor[0] = clearColor[0];
	sampled.BorderColor[1] = clearColor[1];
	sampled.BorderColor[2] = clearColor[2];
	sampled.BorderColor[3] = clearColor[3];
	sampled.MinLOD = 0;
	sampled.MaxLOD = 0;

	// create a sampler state
	if (FAILED(hr = m_dev->CreateSamplerState(
	&sampled,
	&m_samplerState)))
	throw GFX_EXCEPTION(hr);

	m_devContext->PSSetSamplers(
		0,
		1,
		m_samplerState.GetAddressOf());






}

RenderV2::~RenderV2()
{
	/*
	if (m_dev.Get() != nullptr) m_dev->Release();
	if (m_devContext.Get() != nullptr) m_devContext->Release();
	if (m_SwapChain.Get() != nullptr) m_SwapChain->Release();
	if (m_RenderTargetView.Get() != nullptr) m_RenderTargetView->Release();
	*/
}

void RenderV2::build()
{
	vertices.clear();
					  //  x,     y,    tu,   tv
	vertices.push_back({ -1.0f, -1.0f, 0.0f, 1.0f });
	vertices.push_back({ -1.0f,  1.0f, 0.0f, 0.0f });
	vertices.push_back({  1.0f,  1.0f, 1.0f, 0.0f });
									 
	vertices.push_back({  1.0f, -1.0f, 1.0f, 1.0f });
	vertices.push_back({ -1.0f, -1.0f, 0.0f, 1.0f });
	vertices.push_back({  1.0f,  1.0f, 1.0f, 0.0f });





}

void RenderV2::present()
{
	m_devContext->ClearRenderTargetView(
		m_RenderTargetView.Get(),
		clearColor);

	const UINT stride = sizeof(Vertex2DTextured);
	const UINT offset = 0u;

	D3D11_BUFFER_DESC bd = {};
	bd.ByteWidth = vertices.size() * sizeof(Vertex2DTextured);
	bd.StructureByteStride = stride;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices.data();
	HRESULT hr;

	if (FAILED(hr = m_dev->CreateBuffer(
		&bd,
		&sd,
		&m_vertexBuffer)))
		throw GFX_EXCEPTION(hr);

	m_devContext->IASetVertexBuffers(
		0u,
		1u,
		m_vertexBuffer.GetAddressOf(),
		&stride,
		&offset);

	m_devContext->Draw((UINT)vertices.size(), 0);
	m_SwapChain->Present(1, 0);
}

// loads a shader file into memory as an vector of characters
std::vector<char> RenderV2::LoadShaderFromFile(std::string fileName)
{
	// open file
	std::ifstream file(fileName, std::ios::in | std::ios::binary);

	if (file.fail())
		GFX_EXCEPTION("Error opening Shader file: ");
	

	file.seekg(0, std::ios::end);
	int length = file.tellg();
	file.seekg(0, std::ios::beg);
	file.clear();

	std::vector<char> fileData(length);

	file.read(fileData.data(), length);
	file.close();

	return fileData;
}


float charToFloat(unsigned char ch)
{
	return (float)ch / 255.0f;
}

// sets the clear color using character stored values
void RenderV2::setClearColor(unsigned char r, unsigned char g, unsigned char b)
{
	setClearColorf(
		charToFloat(r),
		charToFloat(g),
		charToFloat(b),
		1.0f);
}

// sets clear color using floating point
void RenderV2::setClearColorf(float r, float g, float b, float a)
{
	clearColor[0] = r; // red
	clearColor[1] = g; // green
	clearColor[2] = b; // blue
	clearColor[3] = a; // alpha
}

void RenderV2::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	//pixels[x + y * m_displayWidth] = Color(r, g, b).getColor();
}

int RenderV2::getDisplayX()
{
	return m_displayWidth;
}

int RenderV2::getDisplayY() 
{
	return m_displayHeight;
}
