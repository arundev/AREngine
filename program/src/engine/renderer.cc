#include "renderer.h"
#include "graphic/light_data.h"

namespace engine {

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	
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

	return DoInit();
}

}
