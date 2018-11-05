#include "plateform.h"

namespace engine {


Plateform::OS Plateform::os_ = Plateform::WINDOWS;
Plateform::GraphicAPI Plateform::graphic_api_ = Plateform::D3D_11;

void Plateform::Init(){
#ifdef _WIN32
	os_ = WINDOWS;
	graphic_api_ = D3D_11;
#elif _android_
	type_ = ANDROID;
	graphic_api_ = GLES_2;
#elif _ios_
	type_ = IOS;
	graphic_api_ = GLES_2;
#endif
}

}