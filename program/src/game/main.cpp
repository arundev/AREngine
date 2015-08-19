#include <stdio.h>
#include "win32.h"
#include "engine.h"

int main(int argc, char *argv[]){
	CreateWnd(800, 600, "hello arun");
	g_engine = new Engine();
	g_engine->Init((int)g_instance, g_wnd);
	MsgLoop();
}