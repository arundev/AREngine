#include "engine_include.h"

using namespace System;

namespace mframwork
{
	public ref class SceneWrap
	{
	public:
		bool Init();
		void Update();
		void Free();
	
		bool LoadModel(String^ file_name);
	};
}