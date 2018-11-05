#include "renderer_es2.h"

namespace engine {


RendererEs2::RendererEs2(){

}

RendererEs2::~RendererEs2(){

}

bool RendererEs2::DoInit(){
	if (!CreateContext())
	{
		return false;
	}

	if (!InitGLES())
	{
		return false;
	}

	return true;
}

bool RendererEs2::CreateContext(){

	memset(&es_context_, 0, sizeof(ESContext));
	es_context_.userData = &user_data_;

	GLint flags = ES_WINDOW_RGB;
	EGLint attribList[] =
	{
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		EGL_ALPHA_SIZE, (flags & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
		EGL_DEPTH_SIZE, (flags & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
		EGL_STENCIL_SIZE, (flags & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
		EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
		EGL_NONE
	};

	es_context_.width = (GLint)screen_width_;
	es_context_.height = (GLint)screen_height_;

	EGLint numConfigs;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLDisplay display;
	EGLContext context;
	EGLSurface surface;
	EGLConfig config;
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

	display = eglGetDisplay(GetDC((HWND)window_));

	if (display == EGL_NO_DISPLAY){
		return false;
	}
	if (!eglInitialize(display, &majorVersion, &minorVersion)){
		return false;
	}
	if (!eglGetConfigs(display, NULL, 0, &numConfigs)){
		return false;
	}
	if (!eglChooseConfig(display, attribList, &config, 1, &numConfigs)){
		return false;
	}
	surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)window_, NULL);
	if (surface == EGL_NO_SURFACE){
		return false;
	}
	context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
	if (context == EGL_NO_CONTEXT){
		return false;
	}
	if (!eglMakeCurrent(display, surface, surface, context)){
		return false;
	}

	es_context_.eglDisplay = display;
	es_context_.eglSurface = surface;
	es_context_.eglContext = context;
}

int RendererEs2::InitGLES(){
	UserData *userData = (UserData*)es_context_.userData;
	GLbyte vShaderStr[] =
		"attribute vec4 vPosition;    \n"
		"void main()                  \n"
		"{                            \n"
		"   gl_Position = vPosition;  \n"
		"}                            \n";

	GLbyte fShaderStr[] =
		"precision mediump float;\n"\
		"void main()                                  \n"
		"{                                            \n"
		"  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
		"}                                            \n";

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLint linked;

	vertexShader = LoadShader(GL_VERTEX_SHADER, (const char*)vShaderStr);
	fragmentShader = LoadShader(GL_FRAGMENT_SHADER, (const char*)fShaderStr);
	programObject = glCreateProgram();
	if (programObject == 0){
		return 0;
	}

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);
	glBindAttribLocation(programObject, 0, "vPosition");
	glLinkProgram(programObject);
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
	if (!linked){
		GLint infoLen = 0;
		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1){
			char* infoLog = (char*)malloc(sizeof(char)*infoLen);
			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
			//esLogMessage("Error linking program:\n%s\n", infoLog);
			free(infoLog);
		}
		glDeleteProgram(programObject);
		return FALSE;
	}
	userData->programObject = programObject;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void RendererEs2::Update(){
	
}

void RendererEs2::PreRender(const Vector& clear_color)
{

}

void RendererEs2::Render(){
	UserData *userData = (UserData*)es_context_.userData;
	GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f };

	glViewport(0, 0, es_context_.width, es_context_.height);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(userData->programObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	eglSwapBuffers(es_context_.eglDisplay, es_context_.eglSurface);
}

void RendererEs2::PostRender()
{

}

void RendererEs2::Free(){

}

GLint RendererEs2::LoadShader(GLenum type, const char *shaderSrc){
	GLuint shader;
	GLint compiled;
	shader = glCreateShader(type);
	if (shader == 0){
		return 0;
	}

	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char)*infoLen);
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			//esLogMessage("Error compiling shader:\n%s\n", infoLog);
			free(infoLog);
		}
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}


}