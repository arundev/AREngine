#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

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
	virtual void Free() = 0;

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

private:

};

#endif // !ENGINE_RENDERER_H
