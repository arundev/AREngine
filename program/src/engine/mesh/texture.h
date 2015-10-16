#ifndef ENGINE_MESH_TEXTURE_H
#define ENGINE_MESH_TEXTURE_H

#include "../engine_pch.h"

class Texture
{
public:
	Texture();
	virtual ~Texture();

	static Texture* Create(const char* file_name);

	virtual bool Init(const char* file_name);
	virtual void Free();

	const string& file_name()const{ return file_name_; }
	const unsigned char* tex_data()const{ return tex_data_; }

protected:
	virtual bool DoInit() = 0;
	virtual void DoFree() = 0;

protected:
	string file_name_;
	unsigned char* tex_data_;
	float width_;
	float height_;
};

#endif // ENGINE_MESH_TEXTURE_H