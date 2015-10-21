#ifndef ENGINE_LOG_H
#define ENGINE_LOG_H

#include "..\engine_pch.h"

class Log
{
protected:
	Log();

	std::wofstream	AppLog;

public:

	static Log& Get();

	bool Open();
	bool Close();

	bool Write(const wchar_t *TextString);
	bool Write(std::wstring& TextString);
	bool WriteSeparater();
};

#endif // ENGINE_LOG_H