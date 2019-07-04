#ifndef ENGINE_SCENE_LIGHT_H
#define ENGINE_SCENE_LIGHT_H

#include "node.h"
#include "graphic/light_data.h"
#include "mesh/mesh_light.h"

namespace engine {
	class Light : public Node
	{
	public:
		Light();
		Light(LightType type);
		~Light();
		
		const LightData& light_data()const { return light_data_; }
		void set_light_data(const LightData& data) { light_data_ = data; }

		void set_color(const Color& color) { light_data_.color = color; }
		void set_direction(const Vector& v) { light_data_.direction = v; }
		void set_spot_angle(float f) { light_data_.spot_angle = f; }
		void set_constant_attenuation(float f) { light_data_.constant_attenuation = f; }
		void set_linear_attenuation(float f) { light_data_.linear_attenuation = f; }
		void set_quadratic_attenuation(float f) { light_data_.quadratic_attenuation = f; }
		void set_light_type(LightType type) { light_data_.light_type = type; }
		void set_enable(int v) { light_data_.light_type = v; }

	protected:
		bool Init(LightType type_);

	private:
		LightData light_data_;
		LightMesh* light_mesh_;
	};
}

#endif // ENGINE_SCENE_LIGHT_H