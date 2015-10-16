#ifndef ENGINE_MESH_TEXTURE_H
#define ENGINE_MESH_TEXTURE_H

#include "../engine_pch.h"
#include <d3d11.h>

class Texture
{
public:
	Texture();
	virtual ~Texture();

	virtual bool Create(const char* file_name);
	virtual void Free();

	const string& file_name()const{ return file_name_; }
	const unsigned char* tex_data()const{ return tex_data_; }
	ID3D11ShaderResourceView* texture_view(){ return d3d_texture_view_; }

protected:
	string file_name_;
	unsigned char* tex_data_;
	float width_;
	float height_;

	ID3D11Texture2D* d3d_texture_;
	ID3D11ShaderResourceView* d3d_texture_view_;
};

#endif // ENGINE_MESH_TEXTURE_H