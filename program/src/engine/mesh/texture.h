#ifndef ENGINE_MESH_TEXTURE_H
#define ENGINE_MESH_TEXTURE_H

#include "../engine_pch.h"

class Texture
{
public:

	enum Type 
	{
		TEX_TYPE_BASE = 0,
		TEX_TYPE_NORMAL,
		TEX_TYPE_SPECULAR,

		TEX_TYPE_UNKNOWN
	};

	Texture();
	virtual ~Texture();

	static Texture* Create(const char* file_name, Texture::Type type = Texture::TEX_TYPE_UNKNOWN);

	virtual bool Init(const char* file_name);
	virtual void Free();
	
	void SetType(Texture::Type type) { type_ = type; }

	const string& file_name()const{ return file_name_; }
	const Texture::Type type()const { return type_; }
	const unsigned char* tex_data()const{ return tex_data_; }

protected:
	virtual bool DoInit() = 0;
	virtual void DoFree() = 0;

protected:
	string file_name_;
	Texture::Type type_;
	unsigned char* tex_data_;
	float width_;
	float height_;
};

#endif // ENGINE_MESH_TEXTURE_H