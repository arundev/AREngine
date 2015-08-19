#include "renderer_dx11.h"

#include "../log.h"

#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "DXGI.lib" )


RendererDx11::RendererDx11()
{

}

RendererDx11::~RendererDx11()
{

}

bool RendererDx11::Init(int hInst, int hWnd)
{
	HRESULT hr = S_OK;

	// 创建DXGI对象
	IDXGIFactory1* pFactory = NULL;
	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory));
	if (FAILED(hr))
	{
		return false;
	}

	// 枚举设备
	IDXGIAdapter1* pAdapter;
	std::vector<IDXGIAdapter*> vcAdapters;
	while (pFactory->EnumAdapters1(static_cast<UINT>(vcAdapters.size()), &pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		vcAdapters.push_back(pAdapter);

		DXGI_ADAPTER_DESC1 desc;
		pAdapter->GetDesc1(&desc);

		Log::Get().Write(desc.Description);
	}

	// 创建设备
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL level[] = { D3D_FEATURE_LEVEL_10_0};
	D3D_FEATURE_LEVEL CreatedLevel;

	ID3D11DeviceContext* pDeveiceContext;
	for (auto adapter : vcAdapters)
	{
		hr = D3D11CreateDevice(
			adapter,
			D3D_DRIVER_TYPE_UNKNOWN,
			nullptr,
			createDeviceFlags,
			level,
			1,
			D3D11_SDK_VERSION,
			&device_,
			&CreatedLevel,
			&pDeveiceContext
			);

		if (hr == S_OK)
		{
			break;
		}
	}

	if (FAILED(hr))
	{
		Log::Get().Write(L"init renderer: failed to create d3d device_");
		return false;
	}

	feature_level_ = device_->GetFeatureLevel();

	return true;
}

void RendererDx11::Update()
{

}

void RendererDx11::Free()
{

}