#ifndef ENGINE_GRAPHIC_MATERIAL_DATA_H
#define ENGINE_GRAPHIC_MATERIAL_DATA_H

#include "math/math.h"

namespace engine
{

struct MaterialData
{
	Color emissive = {0.0f, 0.0f, 0.0f, 1.0f};
	Color ambient = {0.1f, 0.1f, 0.0f, 1.0f};
	Color diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
	Color specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	float specular_power = 128.0f;
	bool use_texture = false;
	float padding[2];
};


}

#endif // !ENGINE_GRAPHIC_MATERIAL_DATA_H

