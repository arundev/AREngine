#ifndef ENGINE_ES2_RENDERER_ES2_H
#define ENGINE_ES2_RENDERER_ES2_H

#include "..\engine_pch.h"
#include "..\renderer.h"
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/egl.h>

#define ES_WINDOW_RGB           0
#define ES_WINDOW_ALPHA         1
#define ES_WINDOW_DEPTH         2
#define ES_WINDOW_STENCIL       4
#define ES_WINDOW_MULTISAMPLE   8


class RendererEs2 : public Renderer{
public:
	RendererEs2();
	~RendererEs2();

	struct ESMatrix{
		GLfloat m[4][4];
	};

	struct ESContext{
		void* platformData;
		void* userData;
		GLint width;
		GLint height;
		EGLNativeDisplayType eglNativeDisplay;
		EGLNativeWindowType  eglNativeWindow;
		EGLDisplay eglDisplay;
		EGLContext eglContext;
		EGLSurface eglSurface;

		void(ESCALLBACK *drawFunc) (ESContext *);
		void(ESCALLBACK *shutdownFunc) (ESContext *);
		void(ESCALLBACK *keyFunc) (ESContext *, unsigned char, int, int);
		void(ESCALLBACK *updateFunc) (ESContext *, float deltaTime);
	};

	struct UserData{
		GLuint programObject;
	};


	virtual void Update();
	virtual void PreRender(const Vector& clear_color);
	virtual void Render() = 0;
	virtual void PostRender();
	virtual void Free();

protected:
	virtual bool DoInit();
	
private:
	bool CreateContext();
	int InitGLES();
	GLint LoadShader(GLenum type, const char *shaderSrc);
private:
	UserData user_data_;
	ESContext es_context_;
};

#endif // ENGINE_ES2_RENDERER_ES2_H