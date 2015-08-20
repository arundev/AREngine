#ifndef ENGINE_ENGINE_PCH_H
#define ENGINE_ENGINE_PCH_H

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

// windows
#if _WIN32
#include <Windows.h>
#endif

// android

// ios

// engine
#include "util.h"

// util macro
#define SAFE_RELEASE( x ) {if(x){(x)->Release();(x)=NULL;}}
#define SAFE_DELETE( x ) {if(x){delete (x);(x)=NULL;}}
#define SAFE_DELETE_ARRAY( x ) {if(x){delete[] (x);(x)=NULL;}}

#define NUM_THREADS 4
#define GLYPH_PI 3.14159265f

#ifdef WIN32
#define ESUTIL_API  __cdecl
#define ESCALLBACK  __cdecl
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

#endif // ENGINE_ENGINE_PCH_H