#include "texture_dx11.h"
#include "renderer_dx11.h"
#include "../util/image_util.h"
#include "WICTextureLoader.h"

namespace engine {


TextureDx11::TextureDx11():
d3d_texture_(NULL),
d3d_texture_view_(NULL),
texture_samper_state_(NULL){

}

TextureDx11::~TextureDx11(){
	
}

bool TextureDx11::DoInit() {

	RendererDx11* renderer = RendererDx11::Instance();
	ID3D11Device* device = renderer->device();
	ID3D11DeviceContext* deveice_contex = renderer->device_context();

	// create d3d texture resource
	//std::string full_path = g_file_util->GetTextureFolder() + file_name_.c_str();
	std::string full_path = file_name_.c_str();
	if (!g_file_util->FileExists(full_path))
	{
		return false;
	}


	//HRESULT hr = DirectX::CreateWICTextureFromFile(device,
	//	wstr,
	//	(ID3D11Resource**)&d3d_texture_,
	//	&d3d_texture_view_,
	//	10);
	//if (FAILED(hr)) {
	//	return false;
	//}

	//full_path = "../../bin/res/model/models-nonbsd/FBX/2013_ASCII/jeep1.jpg";
	//full_path = "../../bin/res/model/crytek-sponza/crytek-sponza/textures/sponza_thorn_diff.tga";
	//full_path = "../../bin/res/model/crytek-sponza/crytek-sponza/textures/sponza_thorn_diff.png";

	WCHAR wstr[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, full_path.c_str(), -1, wstr, sizeof(wstr));
	HRESULT hr = DirectX::CreateWICTextureFromFile(device, wstr, nullptr, &d3d_texture_view_);
	if (FAILED(hr)) {

		string log = string("error: failed to D3DX11CreateShaderResourceViewFromFile, path = ") + full_path;
		g_log->Write(log);

		full_path = "../../bin/res/default_texture.png";
		MultiByteToWideChar(CP_ACP, 0, full_path.c_str(), -1, wstr, sizeof(wstr));
		hr = DirectX::CreateWICTextureFromFile(device, wstr, nullptr, &d3d_texture_view_);
		if (FAILED(hr)) {
			hr = GetLastError();
			return false;
		}
	}

	// create texture sampler
	D3D11_SAMPLER_DESC desc;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias = 0.0f;
	desc.MaxAnisotropy = 1;
	//desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	//desc.BorderColor[0] = 0;
	//desc.BorderColor[1] = 0;
	//desc.BorderColor[2] = 0;
	//desc.BorderColor[3] = 0;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = device->CreateSamplerState(&desc, &texture_samper_state_);
	if (FAILED(hr)) {
		Free();
		return false;
	}

	return true;
}

void TextureDx11::DoFree(){
	SAFE_RELEASE(texture_samper_state_);
	SAFE_RELEASE(d3d_texture_);
	SAFE_RELEASE(d3d_texture_view_);
}


}