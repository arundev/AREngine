#include "material.h"
#include <tchar.h>
#include "../camera/camera.h"
#include "../dx11/material_dx11.h"

Material::Material() :
texture_(NULL){

}


Material::~Material(){

}

Material* Material::Create(){
	Material* material = 0;
	if (Plateform::graphic_api() == Plateform::D3D_11){
		material = new MaterialDx11();
	}

	return material;
}

bool Material::Init(){
	SetShader();
	return true;
}

bool Material::Init(const char* vs, const char* ps){
	SetShader(vs, ps);
	return true;
}

bool Material::SetShader(const char* vs /* = NULL */, const char* ps /* = NULL */, const char* gs /* = NULL */){
	if (vs != 0){
		vs_file_name_ = vs;
	}

	if (ps != 0){
		ps_file_name_ = ps;
	}

	if (gs != 0){
		gs_file_name_ = gs;
	}

	return CreateShader();
}

bool Material::SetTexture(const char* file_name){
	SAFE_DELETE(texture_);
	texture_ = Texture::Create(file_name);
	if (texture_ == 0)
	{
		return false;
	}

	return CreateTexture();
}

void Material::Free(){
	DoFree();
	SAFE_FREE(texture_);
}

void Material::Apply(){
	DoApply();
}