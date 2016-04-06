#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "win32.h"
#include "engine_include.h"

Mesh* g_test_trangle = NULL;

int main(int argc, char *argv[]){

	FbxImporterTool import;
	if (import.LoadScene("F:\\workplace\\my\\AREngine\\program\\bin\\res\\model\\Male101.FBX"))
	{
		g_log->Write("fail to load scene from fbx file");
	}
	

	while (true)
	{

	}
}