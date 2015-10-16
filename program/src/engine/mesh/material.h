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
		RTMath::Matrix world_;
		RTMath::Matrix view_;
		RTMath::Matrix projection_;
	};

	static Material* Create();

	bool Init();
	bool Init(const char* vs, const char* ps);
	void Free();
	void Apply();

	virtual bool SetShader(const char* vs = NULL, const char* ps = NULL, const char* gs = NULL);
	virtual bool SetTexture(const char* file_name);

	const string& vs_file_name()const{ return vs_file_name_; }
	const string& ps_file_name()const{ return ps_file_name_; }
	const string& gs_file_name()const{ return gs_file_name_; }

protected:
	virtual bool DoInit() = 0;
	virtual void DoFree() = 0;
	virtual void DoApply() = 0;
	virtual bool CreateShader() = 0;
	virtual bool CreateTexture() = 0;

protected:
	string vs_file_name_;
	string ps_file_name_;
	string gs_file_name_;
	Texture* texture_;
};


#endif // !ENGINE_MODEL_MATERIAL_H
