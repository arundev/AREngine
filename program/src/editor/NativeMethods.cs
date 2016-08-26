using System;
using System.Runtime.InteropServices;

namespace Xilath.Core
{
	internal class NativeMethods
	{
		[StructLayout(LayoutKind.Sequential)]
		public struct Message
		{
			public IntPtr hWnd;
			public IntPtr msg;
			public IntPtr wParam;
			public IntPtr lParam;
			public uint time;
			public System.Drawing.Point p;
		}
		[System.Security.SuppressUnmanagedCodeSecurity]
		[DllImport("User32.dll", CharSet=CharSet.Auto)] //import the User32.dll to get the PeekMessage method
 		public static extern bool PeekMessage(out Message msg, IntPtr hWnd, uint messageFilterMin, uint messageFilterMax, uint flags);
		public NativeMethods()
		{
		}
	}
}
