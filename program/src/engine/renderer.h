#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include "RTMath.h"

using namespace RTMath;

class Renderer{
public:
	Renderer();
	~Renderer();

	enum EType{

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

	const RTMath::Matrix& world_mat()const{ return world_mat_; }
	const RTMath::Matrix& view_mat()const{ return view_mat_; }
	const RTMath::Matrix& projection_mat()const{ return projection_mat_; }

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

	RTMath::Matrix world_mat_;
	RTMath::Matrix view_mat_;
	RTMath::Matrix projection_mat_;

};

#endif // !ENGINE_RENDERER_H
