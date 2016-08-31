#ifndef ENGINE_MODEL_MATERIAL_H
#define ENGINE_MODEL_MATERIAL_H

#include "../engine_pch.h"
#include "texture.h"

class Material
{
public:
	Material();
	virtual ~Material();

	struct MatrixBuffer
	{
		RTMath::Matrix world;
		RTMath::Matrix view;
		RTMath::Matrix projection;
	};

	struct LightingBuffer
	{
		RTMath::Color ambient_light_color;
		float ambient_light_intensity;
		RTMath::Color direction_light_color;
		engine_math::Vector3F direction_light_direction;
	};

	static Material* Create();

	bool Init();
	bool Init(const char* vs, const char* ps);
	void Free();
	void Apply();

	virtual bool SetShader(const char* vs = NULL, const char* ps = NULL, const char* gs = NULL);
	virtual bool SetBaseMap(const char* file_name);
	virtual bool SetNormalMap(const char* file_name);
	virtual bool SetSpecularMap(const char* file_name);

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

protected:
	string vs_file_name_;
	string ps_file_name_;
	string gs_file_name_;
	Texture* base_map_;
	Texture* normal_map_;
	Texture* specular_map_;
};


#endif // !ENGINE_MODEL_MATERIAL_H
