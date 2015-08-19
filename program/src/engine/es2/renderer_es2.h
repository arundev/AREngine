#ifndef ENGINE_ES2_RENDERER_ES2_H
#define ENGINE_ES2_RENDERER_ES2_H

#include "..\engine_pch.h"
#include "..\renderer.h"


typedef struct
{
	GLfloat   m[4][4];
} ESMatrix;

typedef struct ESContext ESContext;
struct ESContext
{

	void       *platformData;
	void       *userData;
	GLint       width;
	GLint       height;

#ifndef __APPLE__
	EGLNativeDisplayType eglNativeDisplay;
	EGLNativeWindowType  eglNativeWindow;
	EGLDisplay  eglDisplay;
	EGLContext  eglContext;
	EGLSurface  eglSurface;
#endif

	void (ESCALLBACK *drawFunc) (ESContext *);
	void (ESCALLBACK *shutdownFunc) (ESContext *);
	void (ESCALLBACK *keyFunc) (ESContext *, unsigned char, int, int);
	void (ESCALLBACK *updateFunc) (ESContext *, float deltaTime);
};

typedef struct{
	GLuint programObject;

} UserData;


#define ES_WINDOW_RGB           0
#define ES_WINDOW_ALPHA         1
#define ES_WINDOW_DEPTH         2
#define ES_WINDOW_STENCIL       4
#define ES_WINDOW_MULTISAMPLE   8



class RendererEs2 : public Renderer
{
public:
	RendererEs2();
	~RendererEs2();

	virtual bool Init(int hInst, HWND hWnd);
	virtual void Update();
	virtual void Free();

protected:
	ESContext es_context_;
};

#endif // ENGINE_ES2_RENDERER_ES2_H