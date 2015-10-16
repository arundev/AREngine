#include "texture.h"
#include "../picture_util.h"
#include "../dx11/renderer_dx11.h"

Texture::Texture():
tex_data_(NULL),
d3d_texture_(NULL),
d3d_texture_view_(NULL){

}

Texture::~Texture(){
	Free();
}

bool Texture::Create(const char* file_name){
	RendererDx11* renderer = RendererDx11::Instance();
	ID3D11Device* deveice = renderer->device();
	ID3D11DeviceContext* deveice_contex = renderer->device_context();

	D3D11_TEXTURE2D_DESC tex_desc;
	D3D11_SHADER_RESOURCE_VIEW_DESC view_desc;
	HRESULT hr = E_FAIL;

	PictureUtil::Data data;
	if (!PictureUtil::Load(file_name, data))	{
		return false;
	}
	tex_data_ = data.data_;
	width_ = data.width_;
	height_ = data.height_;

	tex_desc.Height = data.height_;
	tex_desc.Width = data.width_;
	tex_desc.MipLevels = 0;
	tex_desc.ArraySize = 1;
	tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.Usage = D3D11_USAGE_DEFAULT;
	tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	tex_desc.CPUAccessFlags = 0;
	tex_desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	hr = deveice->CreateTexture2D(&tex_desc, NULL, &d3d_texture_);
	if (FAILED(hr)){
		Free();
		return false;
	}

	unsigned int row_pitch;
	row_pitch = (width_ * 4)*sizeof(unsigned char);
	deveice_contex->UpdateSubresource(d3d_texture_, 0, NULL, tex_data_, row_pitch, 0);

	view_desc.Format = tex_desc.Format;
	view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	view_desc.Texture2D.MostDetailedMip = 0;
	view_desc.Texture2D.MipLevels = -1;
	hr = deveice->CreateShaderResourceView(d3d_texture_, &view_desc, &d3d_texture_view_);
	if (FAILED(hr)){
		Free();
		return false;
	}

	deveice_contex->GenerateMips(d3d_texture_view_);

	return true;
}

void Texture::Free(){
	SAFE_RELEASE(d3d_texture_);
	SAFE_RELEASE(d3d_texture_view_);
	SAFE_DELETE(tex_data_);
}