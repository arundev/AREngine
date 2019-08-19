#include "../engine_pch.h"
#include "log.h"
#include "file_util.h"

namespace engine {


bool Log::Init(){
	FileUtil fs;
	std::string filename = fs.GetLogFolder() + "\\Log.txt";
	AppLog.open(filename.c_str());

	Write("Log file opened.");

	return true;
}

void Log::Free(){
	Write("Log file closed.");
	AppLog.close();
	return;
}

void Log::Update(){

}

bool Log::Write( const char *cTextString )
{
	AppLog << cTextString << "\n";

#if _WIN32
#if _DEBUG 
	::OutputDebugString(cTextString);
	::OutputDebugString("\n");
#endif
#endif

	return true;
}

bool Log::Write( std::string& TextString )
{
	Log::Write( TextString.c_str() );
	AppLog.flush();
	return true;
}

bool Log::WriteSeparater( ){
	Write("------------------------------------------------------------");
	return( true );
}

}