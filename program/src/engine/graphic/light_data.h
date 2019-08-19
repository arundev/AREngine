#ifndef ENGINE_GRAPHIC_LIGHT_DATA_H
#define ENGINE_GRAPHIC_LIGHT_DATA_H

#include "math/math.h"

namespace engine {

	enum LightType
	{
		DirectionalLight = 0,
		PointLight = 1,
		SpotLight = 2
	};


	struct LightData
	{
		Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
		Vector position = { 0.0f, 0.0f, 0.0f, 1.0f };
		Vector direction = { 0.0f, 0.0f, 1.0f, 0.0f };

		float spot_angle = MATH_PIDIV2;
		float constant_attenuation = 1.0f;
		float linear_attenuation = 0.0f;
		float quadratic_attenuation = 0.0f;

		int light_type = DirectionalLight;
		int enabled = 0;
		int padding[2];
	};

}


#endif
