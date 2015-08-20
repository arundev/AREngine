#include "renderer.h"

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
	vsync_enabled_ = false;
	screen_depth_ = 0;
	screen_near_ = 1.0f;

	return DoInit();
}

