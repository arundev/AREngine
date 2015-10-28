#ifndef ENGINE_LOG_H
#define ENGINE_LOG_H

#include "../engine_pch.h"

class Log
{
public:
	Log(){ ; }
	~Log(){ ; }

public:

	bool Init();
	void Update();
	void Free();

	bool Write(const char *TextString);
	bool Write(std::string& TextString);
	bool WriteSeparater();

protected:
	std::wofstream	AppLog;
};

#endif // ENGINE_LOG_H