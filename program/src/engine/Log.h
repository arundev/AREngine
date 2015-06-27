
#pragma once

#include "AREnginePCH.h"

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
