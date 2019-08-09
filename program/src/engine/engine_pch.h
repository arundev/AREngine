#ifndef ENGINE_ENGINE_PCH_H
#define ENGINE_ENGINE_PCH_H

/*-------------------------------------------------------*/
// standard c lib
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory>
#include <assert.h>

// standard c++ lib
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <exception>
using namespace std;


// windows
#if _WIN32
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>  
#include <d3dcommon.h>  
//#include <d3dx10math.h> 
#endif

// android

// ios

// engine
#include "plateform.h"
#include "base/object.h"
#include "util/file_util.h"
#include "util/log.h"
#include "util/string_util.h"
#include "math/math.h"

#include <AntTweakBar.h>
//#if defined(_WIN64)
//#pragma comm
//#endif

//using namespace engine;

/*-------------------------------------------------------*/
// util macro
#define SAFE_RELEASE( x ) {if(x){(x)->Release();(x)=NULL;}}
#define SAFE_DELETE( x ) {if(x){delete (x);(x)=NULL;}}
#define SAFE_FREE(x){if(x){(x)->Free();delete(x);(x)=NULL;}}
#define SAFE_DELETE_ARRAY( x ) {if(x){delete[] (x);(x)=NULL;}}

#ifdef WIN32
#define ESUTIL_API  __cdecl
#define ESCALLBACK  __cdecl
#define RENDERER_DX_11
#else
#define ESUTIL_API
#define ESCALLBACK
#endif

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

namespace engine {

	class Engine;
	class Renderer;
	class BaseCamera;
	class FreeCamera;
	class CameraClass;
	class Log;
	class FileUtil;
}

extern engine::Log* g_log;
extern engine::Engine* g_engine;
extern engine::Renderer* g_renderer;
extern engine::FreeCamera* g_camera;
extern engine::FileUtil* g_file_util;


#endif // ENGINE_ENGINE_PCH_H