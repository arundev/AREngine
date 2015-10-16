#include "util.h"

#if _WIN32
LPCWSTR M2W(const char* src, TCHAR*& dst)
{
	WCHAR wstr[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, src, -1, wstr, sizeof(wstr));
	dst = wstr;
	return wstr;
}

#endif