
#include "file_util.h"
#include <shlobj.h>

FileUtil::FileUtil()
{
}

FileUtil::~FileUtil()
{
}

std::string FileUtil::GetLogFolder()
{
	char buffer[MAX_PATH];

	HRESULT hr = SHGetFolderPath( 0,
	    CSIDL_LOCAL_APPDATA,
		0,
		SHGFP_TYPE_CURRENT,
		buffer
	);

	std::string result = buffer;

	return result;
}

std::string FileUtil::GetDataFolder()
{
	return( data_folder_ );
}

std::string FileUtil::GetModelsFolder()
{
	return( data_folder_ + models_sub_folder_ );
}

std::string FileUtil::GetScriptsFolder()
{
	return( data_folder_ + scripts_sub_folder_ );
}

std::string FileUtil::GetShaderFolder()
{
	return( data_folder_ + shader_sub_folder_ );
}

std::string FileUtil::GetTextureFolder()
{
	return( data_folder_ + texture_sub_folder_ );
}

std::string FileUtil::GetConfigFolder() {
	return data_folder_ + config_sub_folder_;
}

void FileUtil::SetDataFolder(const std::string& folder)
{
	string temp = folder;
	char end = folder[folder.length() - 1];
	if (end != '/' && end != '\\')
	{
		temp += "/";
	}

	data_folder_ = temp;
}

void FileUtil::SetModelsFolder(const std::string& folder)
{
	string temp = folder;
	char end = folder[folder.length() - 1];
	if (end != '/' && end != '\\') {
		temp += "/";
	}

	models_sub_folder_ = temp;
}

void FileUtil::SetScriptsFolder(const std::string& folder)
{
	string temp = folder;
	char end = folder[folder.length() - 1];
	if (end != '/' && end != '\\') {
		temp += "/";
	}

	scripts_sub_folder_ = temp;
}

void FileUtil::SetShaderFolder(const std::string& folder)
{
	string temp = folder;
	char end = folder[folder.length() - 1];
	if (end != '/' && end != '\\') {
		temp += "/";
	}

	shader_sub_folder_ = temp;
}

void FileUtil::SetTextureFolder(const std::string& folder)
{
	string temp = folder;
	char end = folder[folder.length() - 1];
	if (end != '/' && end != '\\') {
		temp += "/";
	}

	texture_sub_folder_ = temp;
}

void FileUtil::SetConfigFolder(const std::string& folder) {
	string temp = folder;
	char end = folder[folder.length() - 1];
	if (end != '/' && end != '\\') {
		temp += "/";
	}

	config_sub_folder_ = temp;
}

bool FileUtil::FileExists(const std::string& file)
{
	// Check if the file exists, and that it is not a directory
	DWORD dwAttrib = GetFileAttributes( file.c_str() );
	bool exist = (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	if (!exist)
	{
		std::string str = "file not find: " + file;
		g_log->Write(str);
	}

	return exist;
}

bool FileUtil::FileIsNewer(const std::string& file1, const std::string& file2)
{
	// This method assumes that the existance of the files has already been verified!

	HANDLE handle1 = INVALID_HANDLE_VALUE;
	HANDLE handle2 = INVALID_HANDLE_VALUE;

	// Get the file handles for the two files
//#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
//    handle1 = CreateFile2( file1.c_str(),
//                           GENERIC_READ,
//                           FILE_SHARE_READ,
//                           OPEN_EXISTING,
//                           nullptr );
//#else
    handle1 = CreateFile( file1.c_str(),
						   GENERIC_READ,
                           FILE_SHARE_READ,
                           nullptr,
                           OPEN_EXISTING,
                           FILE_ATTRIBUTE_NORMAL,
                           nullptr );
//#endif


//#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
//    handle2 = CreateFile2( file2.c_str(),
//                           GENERIC_READ,
//                           FILE_SHARE_READ,
//                           OPEN_EXISTING,
//                           nullptr );
//#else
    handle2 = CreateFile( file2.c_str(),
						   GENERIC_READ,
                           FILE_SHARE_READ,
                           nullptr,
                           OPEN_EXISTING,
                           FILE_ATTRIBUTE_NORMAL,
                           nullptr );
//#endif

	FILETIME fileTime1;
	FILETIME fileTime2;

	// Get the file's time info
	GetFileTime( handle1, nullptr, nullptr, &fileTime1 );
	GetFileTime( handle2, nullptr, nullptr, &fileTime2 );

	// Close the files
	CloseHandle( handle1 );
	CloseHandle( handle2 );

	// Return the comparison
	if ( fileTime1.dwHighDateTime > fileTime2.dwHighDateTime ) {
		return( true );
	} else if ( fileTime1.dwHighDateTime == fileTime2.dwHighDateTime ) {
		return( fileTime1.dwLowDateTime > fileTime2.dwLowDateTime );
	}

	return( false );
}
