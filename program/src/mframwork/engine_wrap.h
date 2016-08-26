
#include "engine_include.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Windows;

namespace mframwork
{
	public enum class MKeyCode
	{
		A,
		D,
		W,
		S,
		Q,
		E,
		MouseLeft,
		MouseRight,
		MouseMid,

		Undefine,
	};

	public ref class MVector2
	{
	public:
		MVector2(float f1, float f2)
		{
			x = f1;
			y = f2;
		}
		MVector2()
		{
			x = y = 0.0f;
		}

		float x, y;
	};


	public ref class EngineWrap
	{
	public:
		bool Init(int width, int height, IntPtr ptWnd, IntPtr ptInst);
		void Update();
		void Free();

		void OnKeyDown(MKeyCode key);
		void OnKeyUp(MKeyCode key);
		void OnMouseDown(MKeyCode btn, MVector2^ pos);
		void OnMouseUp(MKeyCode btn, MVector2^ pos);
		void OnMouseMove(MKeyCode pressBtn, MVector2^ pos);

	private:
	};
}

