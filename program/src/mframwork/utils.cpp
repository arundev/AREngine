#include "Stdafx.h"
#include "utils.h"

using namespace mframwork;

const char* Utils::StringToCharArray(String^ str){
	return (const char*)(Marshal::StringToHGlobalAnsi(str).ToPointer());
}