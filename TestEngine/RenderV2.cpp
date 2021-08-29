#include "RenderV2.h"

RenderV2::RenderV2(HWND hWnd)
{
	//getAdapters();
}

RenderV2::~RenderV2()
{


}

void RenderV2::build()
{
	
}


void RenderV2::send()
{

}
/*
void RenderV2::getAdapters()
{
	UINT i = 0;
	IDXGIAdapter* adapter;
	std::vector<IDXGIAdapter*> adapterList;
	while (mdxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);

		std::wstring text = L"***Adapter: ";
		text += desc.Description;
		text += L"\n";

		OutputDebugString(text.c_str());

		adapterList.push_back(adapter);
		++i;
	}

	for (size_t i = 0; i < adapterList.size(); ++i)
	{
		adapterList[i]->Release();
	}
}*/