#include "renderer_es2.h"

RendererEs2::RendererEs2()
{

}

RendererEs2::~RendererEs2()
{

}

EGLint GetContextRenderableType(EGLDisplay eglDisplay)
{
#ifdef EGL_KHR_create_context
	const char *extensions = eglQueryString(eglDisplay, EGL_EXTENSIONS);

	// check whether EGL_KHR_create_context is in the extension string
	if (extensions != NULL && strstr(extensions, "EGL_KHR_create_context"))
	{
		// extension is supported
		return EGL_OPENGL_ES3_BIT_KHR;
	}
#endif
	// extension is not supported
	return EGL_OPENGL_ES2_BIT;
}

bool RendererEs2::Init(int hInst, HWND hWnd)
{
	memset(&es_context_, 0, sizeof (ESContext));
	es_context_.userData = malloc(sizeof(UserData));
	es_context_.eglNativeWindow = (HWND)hWnd;

	EGLConfig config;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLint contextAttributs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };

	es_context_.eglDisplay = eglGetDisplay(GetDC(hWnd));
	if (es_context_.eglDisplay == EGL_NO_DISPLAY)
	{
		//return false;
	}

	if (!eglInitialize(es_context_.eglDisplay, &majorVersion, &minorVersion))
	{
		return false;
	}

	EGLint flags = ES_WINDOW_RGB;
	EGLint numConfigs = 0;
	EGLint attribList[] =
	{
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		EGL_ALPHA_SIZE,		(flags & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
		EGL_DEPTH_SIZE,		(flags & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
		EGL_STENCIL_SIZE,	(flags & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
		EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,

		EGL_RENDERABLE_TYPE, GetContextRenderableType(es_context_.eglDisplay),
		EGL_NONE
	};

	if(!eglChooseConfig(es_context_.eglDisplay, attribList, &config, 1, &numConfigs))
	{
		return false;
	}

	if (numConfigs < 1)
	{
		return false;
	}

	return true;
}

void RendererEs2::Update()
{

}

void RendererEs2::Free()
{

}