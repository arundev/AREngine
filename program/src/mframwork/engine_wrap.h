
#include "engine_include.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace mframwork
{
	public ref class EngineWrap
	{
	public:
		bool Init(int width, int height, IntPtr ptWnd, IntPtr ptInst);
		void Update();
		void Free();

	private:
	};
}

