#include "renderer.h"
#include "graphic/light_data.h"

namespace engine {

Renderer::Renderer() : default_direction_light_(nullptr)
{

}

Renderer::~Renderer()
{
	SAFE_DELETE(default_direction_light_);
}

bool Renderer::Init(const Window& param)
{
	window_ = param.wnd_;
	instance_ = param.instance_;
	screen_width_ = param.width_;
	screen_height_ = param.height_;

	full_screen_ = false;
	vsync_enabled_ = true;
	screen_far_ = 10000.0f;
	screen_near_ = 0.1f;


	fill_mode_ = Renderer::FillMode::kFillModeSolide;
	cull_mode_ = Renderer::CullMode::kCullModeBack;

	default_direction_light_ = new LightData();
	default_direction_light_->light_type = LightType::DirectionalLight;
	default_direction_light_->color = Color(1.0f, 0.0f, 0.0f);
	light_list_.push_back(default_direction_light_);

	return DoInit();
}

}
