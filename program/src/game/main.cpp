#pragma

#include <stdio.h>
#include "win32.h"
#include "AREngine.h"

int main(int argc, char *argv[])
{

	createWnd(800, 600, "hello arun");

	gEngine = new AREngine();
	gEngine->init((int)gMainInst, (int)gMainWnd);

	msgLoop();
}