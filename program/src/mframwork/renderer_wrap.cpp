#include "Stdafx.h"
#include "renderer_wrap.h"

using namespace mframwork;

void RendererWrap::SetWireframe(bool b){
	g_renderer->SetWireframe(b);
}