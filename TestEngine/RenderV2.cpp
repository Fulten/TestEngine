#include "RenderV2.h"

RenderV2::RenderV2(HWND& hWnd) :
	m_bufferCount(1)
{
	m_displayHeight = 600;
	m_displayWidth = 600;

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = m_bufferCount; // 1 buffers for now
	sd.BufferDesc.Width = m_displayWidth; // 600 x 600
	sd.BufferDesc.Height = m_displayHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60; // 60 fps
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1; // controls super sampleing
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	HRESULT hr;

	// create our devices
	if(FAILED(hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		&FeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&sd,
		m_SwapChain.GetAddressOf(),
		m_dev.GetAddressOf(),
		nullptr,
		&m_devContext)))
	throw GFX_EXCEPTION(hr);
		
	

}

RenderV2::~RenderV2()
{


}

void RenderV2::build()
{
	

}

void RenderV2::present()
{

	

}

