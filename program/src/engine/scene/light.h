#ifndef ENGINE_SCENE_LIGHT_H
#define ENGINE_SCENE_LIGHT_H

#include "node.h"
#include "graphic/light_data.h"

namespace engine {
	class Light : public Node
	{
	public:
		Light();
		~Light();
		
		const LightData& light_data()const { return light_data_; }
		void set_light_data(const LightData& data) { light_data_ = data; }

	protected:
	private:
		LightData light_data_;
	};
}

#endif // ENGINE_SCENE_LIGHT_H