#pragma once



#include "Win.h"
#include <d3d11.h>
#include <vector>
#include <string>
#include <fstream>

#pragma comment (lib, "d3d11.lib")

struct pixel
	{
		unsigned char r;
		unsigned char b;
		unsigned char g;
		unsigned char x;
	};

class Texture2D
{
private:
	bool success;
	std::vector<pixel> imageData;
	D3D11_TEXTURE2D_DESC tex2dDesc = {};

	bool create(std::string fileName)
	{
		// open file
		std::fstream file(fileName, std::ios::in | std::ios::binary);
		if (file.fail())
			return false;

		file.seekg(0, std::ios::end);
		int length = file.tellg();
		file.seekg(0, std::ios::beg);
		file.clear();

		BITMAPFILEHEADER bmpHead = {};
		file.read((char*)&bmpHead, sizeof(bmpHead));
		BITMAPINFO bmpInfo = {};
		file.read((char*)&bmpInfo, sizeof(bmpInfo));

		int offset = bmpHead.bfOffBits;
		length -= offset;
		file.seekg(offset, std::ios::beg);
		std::vector<pixel> fileData(length * 0.25);

		tex2dDesc.Width = bmpInfo.bmiHeader.biWidth;
		tex2dDesc.Height = bmpInfo.bmiHeader.biHeight;
		tex2dDesc.MipLevels = tex2dDesc.ArraySize = 1;
		tex2dDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		tex2dDesc.SampleDesc.Count = 1;
		tex2dDesc.Usage = D3D11_USAGE_DYNAMIC;
		tex2dDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		tex2dDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		tex2dDesc.MiscFlags = 0;

		struct bmpPix
		{
			unsigned char b;
			unsigned char g;
			unsigned char r;
			unsigned char x;
		};

		// account for bmp with inverse height
		if (bmpInfo.bmiHeader.biHeight > 0)
			for (int y = bmpInfo.bmiHeader.biHeight - 1; y >= 0; y--)
			{
				for (int x = 0; x < bmpInfo.bmiHeader.biWidth; x++)
				{
					bmpPix temp = {};
					file.read((char*)&temp, sizeof(temp));
					fileData[x + y * bmpInfo.bmiHeader.biWidth] = pixel{ temp.r, temp.g, temp.b, temp.x };
				}
			}
		else
			for (int y = 0; y < bmpInfo.bmiHeader.biHeight * -1; y++)
			{
				for (int x = 0; x < bmpInfo.bmiHeader.biWidth; x++)
				{
					bmpPix temp = {};
					file.read((char*)&temp, sizeof(temp));
					fileData[x + y * bmpInfo.bmiHeader.biWidth] = pixel{ temp.r, temp.g, temp.b, temp.x };
				}
			}

		imageData = fileData;
		return true;
	}

public:
	// load a bmp file into memory, must be 32bit xrgb format
	Texture2D(std::string fileName)
	{
		success = create(fileName);
	}

	~Texture2D()
	{}

	HRESULT makeIntoDXGITex(Microsoft::WRL::ComPtr <ID3D11Device>& m_dev, Microsoft::WRL::ComPtr<ID3D11Texture2D>& p_tex2d)
	{
		D3D11_SUBRESOURCE_DATA subRD = {};
		subRD.pSysMem = imageData.data();
		subRD.SysMemPitch = tex2dDesc.Width * 4;
		subRD.SysMemSlicePitch = subRD.SysMemPitch * tex2dDesc.Height;

		HRESULT hr;
		hr = m_dev->CreateTexture2D(
			&tex2dDesc,
			&subRD,
			&p_tex2d);

		return hr;
	}
	
	bool wasCreated()
	{ return success; }

};