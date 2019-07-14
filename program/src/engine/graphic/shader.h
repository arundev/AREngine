#ifndef ENGINE_GRAPHIC_SHADER_H
#define ENGINE_GRAPHIC_SHADER_H
#include "engine_pch.h"

#include "material_data.h"
#include "light_data.h"

#define MAX_LIGHTS_NUM 8

namespace engine 
{
	class Shader
	{
	public:
		Shader() { ; }
		virtual ~Shader() { ; }

		struct MatrixProperty
		{
			Matrix world_mat;
			Matrix world_mat_inverse_transpose; // Äæ¾ØÕóµÄ×°ÖÃ
			Matrix world_view_proj_mat;
		};

		struct MaterialProperty
		{
			MaterialData material;
		};

		struct  LightProperty
		{
			Vector eye_position = { 0.0f, 0.0f, 0.0f, 1.0f };
			Color global_ambient = { 1.2f, 1.2f, 0.8f, 1.0f };

			LightData light[MAX_LIGHTS_NUM];
		};

		virtual bool Init(const std::string& file) { return true; }
		virtual bool Init(const std::string& vs, const std::string& ps) { return true; }
		virtual void Update(float elapse) { ; }
		virtual void Render() { ; }
		virtual void Free() { ; }

		void UpdateMatrixPropterty(const Matrix& world, const Matrix& view, const Matrix& proj);
		void UpdateLightProperty(const std::vector<LightData*>& light_list, const Color& ambient_light, const Vector& eye_pos);
		void UpdateMaterialProperty();

		const MaterialProperty& material_data() { return material_; }
		void set_material_data(const MaterialProperty& material) { material_ = material; }
		void set_material_use_texture(bool b) { material_.material.use_texture = b; }

	protected:
		std::string vs_file_, ps_file_;

		MatrixProperty transform_;
		MaterialProperty material_;
		LightProperty lights_;
	};
}

#endif // !ENGINE_GRAPHIC_SHADER_H

