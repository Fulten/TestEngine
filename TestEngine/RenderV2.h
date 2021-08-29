#pragma once
// 


//#include <wrl.h>
//#include <d3d11.h>
//#include <d3d12.h>
#include <vector>
#include "vec2d.h"
#include "DrawCharString.h"
#include "Color.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3d12.lib")

//Microsoft::WRL::ComPtr






class RenderV2
{
private:
	//Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
	//Microsoft::WRL::ComPtr<IDXGIFactory> mdxgiFactory;

protected:
	void build();
	void send();
	//void getAdapters();



public:
	RenderV2(HWND hWnd);
	~RenderV2();
	RenderV2(const RenderV2& rhs) = delete;
	RenderV2 operator=(const RenderV2& rhs) = delete;



};

