#include <stdio.h>
#include "win32.h"
#include "engine.h"

int main(int argc, char *argv[]){
	CreateWnd(800, 600, "hello arun");
	g_engine = new Engine();

	Renderer::Window param;
	param.width_ = 800;
	param.height_ = 600;
	param.wnd_ = (int)g_wnd;
	param.instance_ = (int)g_instance;

	g_engine->Init(param);
	MsgLoop();
}