#pragma once

#include "..\AREnginePCH.h"
#include "..\ARRenderer.h"


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

typedef struct
{
	// Handle to a program object
	GLuint programObject;

} UserData;


/// esCreateWindow flag - RGB color buffer
#define ES_WINDOW_RGB           0
/// esCreateWindow flag - ALPHA color buffer
#define ES_WINDOW_ALPHA         1
/// esCreateWindow flag - depth buffer
#define ES_WINDOW_DEPTH         2
/// esCreateWindow flag - stencil buffer
#define ES_WINDOW_STENCIL       4
/// esCreateWindow flat - multi-sample buffer
#define ES_WINDOW_MULTISAMPLE   8



class ARRenderEs2 : public ARRenderer
{
public:
	ARRenderEs2();
	~ARRenderEs2();

	virtual bool init(int hInst, int hWnd);
	virtual void update();
	virtual void free();

protected:
	ESContext m_ESContext;
};