#pragma

#include <stdio.h>
#include "win32.h"
#include "arEngine.h"

int main(int argc, char *argv[])
{

	createWnd(800, 600, "hello arun");

	gEngine = new arEngine();
	gEngine->init((int)gMainInst, (int)gMainWnd);

	msgLoop();
}