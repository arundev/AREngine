#include "texture.h"
#include "../util/image_util.h"

#ifdef _WIN32
#include "../dx11/renderer_dx11.h"
#include "../dx11/texture_dx11.h"
#endif


Texture::Texture():
tex_data_(NULL){

}

Texture::~Texture(){

}

Texture* Texture::Create(const char* file_name, Texture::Type type /* = Texture::TEX_TYPE_UNKNOWN */) {
	Texture* texture = 0;
	if (Plateform::graphic_api() == Plateform::D3D_11){
		texture = new TextureDx11();
	}

	if (texture != 0)
	{
		if (!texture->Init(file_name))
		{
			SAFE_DELETE(texture);
		}
		texture->SetType(type);
	}

	return texture;
}

bool Texture::Init(const char* file_name){
	Free();
	file_name_ = file_name;
	
	return DoInit();
}

void Texture::Free(){
	DoFree();
	SAFE_DELETE(tex_data_);
}