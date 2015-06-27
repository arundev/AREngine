#include "ARRendererDx11.h"

#include "../Log.h"

// Library imports
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "DXGI.lib" )


ARRenderDx11::ARRenderDx11()
{

}

ARRenderDx11::~ARRenderDx11()
{

}

bool ARRenderDx11::init(int hInst, int hWnd)
{
	HRESULT hr = S_OK;

	// ����DXGI����
	IDXGIFactory1* pFactory;
	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory));
	if (hr == E_FAIL)
	{
		return false;
	}

	// ö���豸
	IDXGIAdapter1* pAdapter;
	std::vector<IDXGIAdapter*> vcAdapters;
	while (pFactory->EnumAdapters1(static_cast<UINT>(vcAdapters.size()), &pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		vcAdapters.push_back(pAdapter);

		DXGI_ADAPTER_DESC1 desc;
		pAdapter->GetDesc1(&desc);

		Log::Get().Write(desc.Description);
	}

	// �����豸
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL level[] = {};
	D3D_FEATURE_LEVEL CreatedLevel;

	ID3D11DeviceContext* pDeveiceContext;
	for (auto adapter : vcAdapters)
	{
		hr = D3D11CreateDevice(
			adapter,
			D3D_DRIVER_TYPE_UNKNOWN,
			nullptr,
			createDeviceFlags,
			1,
			D3D_SDK_VERSION,
			&mDevice,
			)
	}

	return true;
}

void ARRenderDx11::update()
{

}

void ARRenderDx11::free()
{

}