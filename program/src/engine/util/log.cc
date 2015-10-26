
#include "log.h"
#include "file_system.h"

Log::Log()
{
}

Log& Log::Get()
{
	static Log log;
	return( log );
}

bool Log::Open()
{
	FileSystem fs;
	std::string filename = fs.GetLogFolder() + "\\Log.txt";
	AppLog.open( filename.c_str() );

	Write( "Log file opened." );

	return( true );
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

	return( true );
}

bool Log::Write( std::string& TextString )
{
	Log::Write( TextString.c_str() );
	AppLog.flush();
	return( true );
}

bool Log::Close( )
{
	Write( "Log file closed." );
	AppLog.close();
	return( true );
}

bool Log::WriteSeparater( )
{
	Write("------------------------------------------------------------" );

	return( true );
}