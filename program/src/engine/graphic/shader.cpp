#include "shader.h"

namespace engine
{

void Shader::UpdateMatrixPropterty(const Matrix& world, const Matrix& view, const Matrix& proj)
{
	transform_.world_mat = world;

	Matrix inverse;
	inverse.InverseOf(world);
	transform_.world_mat_inverse_transpose.TransposeOf(inverse);

	Matrix wvp = world * view * proj;
	//transform_.world_view_proj_mat.TransposeOf(wvp);
	transform_.world_view_proj_mat = wvp;
}

void Shader::UpdateLightProperty(const std::vector<LightData*>& light_list, const Color& ambient_light, const Vector& eye_pos)
{
	int index = 0;
	for (; index <light_list.size() && index < MAX_LIGHTS_NUM; index++)
	{
		lights_.light[index] = *light_list[index];
	}

	for (int i= index; i < MAX_LIGHTS_NUM; i++)
	{
		lights_.light[index].enabled = false;
	}

	lights_.global_ambient = ambient_light;
	lights_.eye_position = eye_pos;
}

void Shader::UpdateMaterialProperty()
{
	material_.material.ambient = { 0.25f, 0.20725f, 0.20725f, 1.0f };
	material_.material.diffuse = { 1.0f, 0.829f, 0.829f, 1.0f };
	material_.material.specular = { 0.296648f, 0.296648f, 0.296648f, 1.0f };
	material_.material.specular_power = 11.264f;
}

}