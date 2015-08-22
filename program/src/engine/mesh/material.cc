#include "material.h"

Material::Material() :
vertex_shader_(NULL),
geometry_shader_(NULL),
pixel_shader_(NULL)
{

}

Material::~Material(){
	Free();
}

bool Material::Create(const char* vs, const char* gs, const char* ps){
	return true;
}

void Material::Free(){
	SAFE_RELEASE(vertex_shader_);
	SAFE_RELEASE(geometry_shader_);
	SAFE_RELEASE(pixel_shader_);
}