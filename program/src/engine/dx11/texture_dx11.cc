#include "texture_dx11.h"
#include "renderer_dx11.h"
#include "../util/image_util.h"
#include <WICTextureLoader.h>
#include <D3DX11tex.h>

TextureDx11::TextureDx11():
d3d_texture_(NULL),
d3d_texture_view_(NULL),
texture_samper_state_(NULL){

}

TextureDx11::~TextureDx11(){
	
}

//bool TextureDx11::DoInit() {
//	RendererDx11* renderer = RendererDx11::Instance();
//	ID3D11Device* device = renderer->device();
//	ID3D11DeviceContext* deveice_contex = renderer->device_context();
//
//	D3D11_TEXTURE2D_DESC tex_desc;
//	D3D11_SHADER_RESOURCE_VIEW_DESC view_desc;
//	HRESULT hr = E_FAIL;
//
//	ImageUtil::Data data;
//	WCHAR wstr[MAX_PATH] = { 0 };
//	//MultiByteToWideChar(CP_ACP, 0, full_path.c_str(), -1, wstr, sizeof(wstr));
//	if (!ImageUtil::Load("stone01.tga", data)) {
//		return false;
//	}
//	tex_data_ = data.data_;
//	width_ = data.width_;
//	height_ = data.height_;
//
//	tex_desc.Height = data.height_;
//	tex_desc.Width = data.width_;
//	tex_desc.MipLevels = 0;
//	tex_desc.ArraySize = 1;
//	tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	tex_desc.SampleDesc.Count = 1;
//	tex_desc.SampleDesc.Quality = 0;
//	tex_desc.Usage = D3D11_USAGE_DEFAULT;
//	tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
//	tex_desc.CPUAccessFlags = 0;
//	tex_desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
//	hr = device->CreateTexture2D(&tex_desc, NULL, &d3d_texture_);
//	if (FAILED(hr)) {
//		Free();
//		return false;
//	}
//
//	unsigned int row_pitch;
//	row_pitch = (width_ * 4)*sizeof(unsigned char);
//	deveice_contex->UpdateSubresource(d3d_texture_, 0, NULL, tex_data_, row_pitch, 0);
//
//	view_desc.Format = tex_desc.Format;
//	view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//	view_desc.Texture2D.MostDetailedMip = 0;
//	view_desc.Texture2D.MipLevels = -1;
//	hr = device->CreateShaderResourceView(d3d_texture_, &view_desc, &d3d_texture_view_);
//	if (FAILED(hr)) {
//		Free();
//		return false;
//	}
//
//	deveice_contex->GenerateMips(d3d_texture_view_);
//
//	return true;
//}


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

	WCHAR wstr[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, full_path.c_str(), -1, wstr, sizeof(wstr));
	//HRESULT hr = DirectX::CreateWICTextureFromFile(device,
	//	wstr,
	//	(ID3D11Resource**)&d3d_texture_,
	//	&d3d_texture_view_,
	//	10);
	//if (FAILED(hr)) {
	//	return false;
	//}
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(device,
		full_path.c_str(),
		0,
		0,
		&d3d_texture_view_,
		0);
	if (FAILED(hr)) {
		hr = GetLastError();
		return false;
	}

	// create texture sampler
	D3D11_SAMPLER_DESC desc;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias = 0.0f;
	desc.MaxAnisotropy = 1;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.BorderColor[0] = 0;
	desc.BorderColor[1] = 0;
	desc.BorderColor[2] = 0;
	desc.BorderColor[3] = 0;
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