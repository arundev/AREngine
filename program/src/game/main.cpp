#include <stdio.h>
#include "win32.h"
#include "engine.h"
#include "mesh/mesh.h"

Mesh* g_test_trangle = NULL;

int main(int argc, char *argv[]){
	CreateWnd(800, 600, "hello arun");
	AppInit();
	MsgLoop();
}

void AppInit(){
	g_engine = new Engine();
	Renderer::Window param;
	param.width_ = 800;
	param.height_ = 600;
	param.wnd_ = (int)g_wnd;
	param.instance_ = (int)g_instance;
	g_engine->Init(param);

	g_test_trangle = Mesh::CreateTriangle();
}

void AppUpdate(){

}

void AppRender(){

}

void AppFree(){

}