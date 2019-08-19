#ifndef ENGINE_DEFINE_H
#define ENGINE_DEFINE_H


// common macro
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

#endif