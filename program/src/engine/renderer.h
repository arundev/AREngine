#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include "engine_pch.h"
#include "graphic/light_data.h"

namespace engine{

class Renderer{
public:
	Renderer();
	~Renderer();

	enum FillMode {
		kFillModeWireframe,
		kFillModeSolide,
	};

	enum CullMode{
		kCullModeNone,
		kCullModeFront,
		kCullModeBack
	};

	struct Window{
		int wnd_;
		int instance_;
		int width_;
		int height_;

		Window(){
		}

		Window(int hwnd, int inst, int width, int height){
			wnd_ = hwnd;
			instance_ = inst;
			width_ = width;
			height_ = height;
		}
	};

	virtual bool Init(const Renderer::Window& param);
	virtual void Update() = 0;
	virtual void PreRender(const engine::Vector& clear_color) = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	virtual void Free() = 0;

	virtual void SetWireframe(bool b) { ; }

	virtual void BeginEvent(const char* name) { ; }
	virtual void EndEvent() { ; }

	const engine::Matrix& world_mat()const{ return world_mat_; }
	void set_world_mat(Matrix& mat) { world_mat_ = mat; }
	const engine::Matrix& view_mat()const{ return view_mat_; }
	void set_view_mat(Matrix& mat) { view_mat_ = mat; }
	const engine::Matrix& projection_mat()const{ return projection_mat_; }
	void set_projection_mat(engine::Matrix& mat) { projection_mat_ = mat; }

	const Renderer::FillMode get_fill_mode()const { return fill_mode_; }
	void set_fill_mode(Renderer::FillMode mode_) { fill_mode_ = mode_; }
	const Renderer::CullMode get_cull_mode()const { return cull_mode_; }
	void set_cull_mode(Renderer::CullMode mode_) { cull_mode_ = mode_; }

	const std::vector<LightData*>& light_list()const { return light_list_; }
	void set_light_list(const std::vector<LightData*>& light) { light_list_ = light; }

protected:
	virtual bool DoInit() = 0;
	virtual void ApplyRenderState() { ; }

protected:
	bool full_screen_;
	bool vsync_enabled_;
	int window_;
	int instance_;
	int screen_width_;
	int screen_height_;
	float screen_far_;
	float screen_near_;	

	Renderer::FillMode fill_mode_;
	Renderer::CullMode cull_mode_;

	engine::Matrix world_mat_;
	engine::Matrix view_mat_;
	engine::Matrix projection_mat_;

	std::vector<LightData*> light_list_;
	LightData* default_direction_light_;
};

}

#endif // !ENGINE_RENDERER_H
