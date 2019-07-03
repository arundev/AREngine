#ifndef ENGINE_GRAPHIC_LIGHT_DATA_H
#define ENGINE_GRAPHIC_LIGHT_DATA_H
#include "engine_pch.h"

namespace engine {

	enum LightType
	{
		DirectionalLight = 0,
		PointLight = 1,
		SpotLight = 2
	};


	struct LightData
	{

		LightData() : color(1.0f, 1.0f, 1.0f, 1.0f)
			, position(0.0f, 0.0f, 0.0f, 1.0f)
			, direction(0.0f, 0.0f, 1.0f, 0.0f)
			, spot_angle(MATH_PIDIV2)
			, constant_attenuation(1.0f)
			, linear_attenuation(0.0f)
			, quadratic_attenuation(0.0f)
			, light_type(DirectionalLight)
			, enabled(0)

		{

		}

		Color color;
		Vector position;
		Vector direction;

		float spot_angle;
		float constant_attenuation;
		float linear_attenuation;
		float quadratic_attenuation;

		int light_type;
		int enabled;
	};

}


#endif
