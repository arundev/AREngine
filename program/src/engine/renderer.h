#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include "engine_pch.h"
#include "RTMath.h"

using namespace RTMath;

class Renderer{
public:
	Renderer();
	~Renderer();

	enum EType{

	};

	enum ECullMode{
		None = 0,
		Front = 1,
		Back = 2,
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
	virtual void PreRender(const Vector& clear_color) = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	virtual void Free() = 0;

	bool wireframe()const { return wireframe_; }
	virtual void set_wireframe(bool b) { wireframe_ = b; }
	virtual void SetCullMode(const Renderer::ECullMode state){ ; }

	virtual void BeginEvent(const char* name) { ; }
	virtual void EndEvent() { ; }


	const RTMath::Color& ambient_light_color()const { return ambient_light_color_; }
	void set_ambient_light_color(const RTMath::Color color) { ambient_light_color_ = color; }
	float ambient_light_intensity() { return ambient_light_intensity_; }
	void set_ambient_light_intensity(float intensity) { ambient_light_intensity_ = intensity; }
	const RTMath::Color& direction_light_color()const { return direction_light_color_; }
	void set_direction_light_color(const RTMath::Color& color) { direction_light_color_ = color; }
	const engine_math::Vector3F& direction_light_direction()const { return direction_light_direction_; }
	void set_direction_light_direction(const engine_math::Vector3F& direction) { direction_light_direction_ = direction; }

	const RTMath::Matrix& world_mat()const{ return world_mat_; }
	void set_world_mat(RTMath::Matrix& mat) { world_mat_ = mat; }
	const RTMath::Matrix& view_mat()const{ return view_mat_; }
	void set_view_mat(RTMath::Matrix& mat) { view_mat_ = mat; }
	const RTMath::Matrix& projection_mat()const{ return projection_mat_; }
	void set_projection_mat(RTMath::Matrix& mat) { projection_mat_ = mat; }

protected:
	virtual bool DoInit() = 0;

protected:
	bool full_screen_;
	bool vsync_enabled_;
	int window_;
	int instance_;
	int screen_width_;
	int screen_height_;
	float screen_depth_;
	float screen_near_;	
	bool wireframe_;

	RTMath::Color ambient_light_color_;
	float ambient_light_intensity_;
	engine_math::Vector3F direction_light_direction_;
	RTMath::Color direction_light_color_;

	RTMath::Matrix world_mat_;
	RTMath::Matrix view_mat_;
	RTMath::Matrix projection_mat_;

};

#endif // !ENGINE_RENDERER_H
