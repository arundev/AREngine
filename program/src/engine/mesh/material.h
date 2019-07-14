#ifndef ENGINE_MODEL_MATERIAL_H
#define ENGINE_MODEL_MATERIAL_H

#include "engine_pch.h"
#include "texture.h"
#include "graphic/shader.h"

namespace engine {


class Material
{
public:
	Material();
	virtual ~Material();

	struct MatrixBuffer
	{
		Matrix world_;
		Matrix view_;
		Matrix projection_;
	};

	static Material* Create();

	virtual bool Init();
	virtual bool Init(const char* vs, const char* ps);
	virtual bool Init(const std::string& shader);
	virtual void Free();
	virtual void Apply();

	virtual bool SetShader(const char* vs = NULL, const char* ps = NULL, const char* gs = NULL);
	virtual bool SetShader(const std::string& file_name);
	virtual bool SetBaseMap(const char* file_name);
	virtual bool SetNormalMap(const char* file_name);
	virtual bool SetSpecularMap(const char* file_name);

	void set_world_transform(const Matrix& ts) { world_mat_ = ts; }
	const Matrix& world_transform()const { return world_mat_; }
	void set_view_transform(const Matrix& mat) { view_mat_ = mat; }
	const Matrix& view_transform()const { return view_mat_; }
	void set_proj_transform(const Matrix& mat) { proj_mat_ = mat; }
	const Matrix& proj_transform()const { return proj_mat_; }


	const string& vs_file_name()const{ return vs_file_name_; }
	const string& ps_file_name()const{ return ps_file_name_; }
	const string& gs_file_name()const{ return gs_file_name_; }

	const Texture* base_map()const { return base_map_; }
	const Texture* normal_map()const { return normal_map_; }
	const Texture* specular_map()const { return specular_map_; }

protected:
	virtual bool DoInit() = 0;
	virtual void DoFree() = 0;
	virtual void DoApply() = 0;
	virtual bool CreateShader() = 0;
	virtual bool CreateShader(const std::string& shader) = 0;
	virtual bool CreateShader(const std::string& vs, const std::string& ps) = 0;

	virtual void InitTransform();

protected:
	Shader* shader_ = nullptr;

	std::string vs_file_name_;
	std::string ps_file_name_;
	std::string gs_file_name_;
	std::string shader_file_name_;

	Texture* base_map_ = nullptr;
	Texture* normal_map_ = nullptr;
	Texture* specular_map_ = nullptr;

	Matrix world_mat_, view_mat_, proj_mat_;
	Matrix world_view_proj_mat_;
};


}

#endif // !ENGINE_MODEL_MATERIAL_H
