#include "material.h"
#include <tchar.h>
#include "../camera/camera.h"
#include "../dx11/material_dx11.h"

Material::Material() :
base_map_(NULL),
normal_map_(NULL),
specular_map_(NULL){

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

bool Material::SetBaseMap(const char* file_name) {
	SAFE_FREE(base_map_);
	base_map_ = Texture::Create(file_name, Texture::TEX_TYPE_BASE);
	return base_map_ != NULL;
}

bool Material::SetNormalMap(const char* file_name) {
	SAFE_FREE(normal_map_);
	normal_map_ = Texture::Create(file_name, Texture::TEX_TYPE_NORMAL);
	return base_map_ != NULL;
}

bool Material::SetSpecularMap(const char* file_name) {
	SAFE_FREE(specular_map_);
	specular_map_ = Texture::Create(file_name, Texture::TEX_TYPE_SPECULAR);
	return specular_map_ != NULL;
}

void Material::Free(){
	DoFree();
	SAFE_FREE(base_map_);
	SAFE_FREE(normal_map_);
	SAFE_FREE(specular_map_);
}

void Material::Apply(){
	DoApply();
}