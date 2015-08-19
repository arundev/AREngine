
#include "file_system.h"
#include <shlobj.h>

std::wstring FileSystem::data_folder_ = L"../Data/";
std::wstring FileSystem::models_sub_folder_ = L"Models/";
std::wstring FileSystem::scripts_sub_folder_ = L"Scripts/";
std::wstring FileSystem::shader_sub_folder_ = L"Shaders/";
std::wstring FileSystem::texture_sub_folder_ = L"Textures/";

FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
}

std::wstring FileSystem::GetLogFolder()
{
	wchar_t buffer[MAX_PATH];

	HRESULT hr = SHGetFolderPath( 0,
	    CSIDL_LOCAL_APPDATA,
		0,
		SHGFP_TYPE_CURRENT,
		buffer
	);

	std::wstring result = buffer;

	return( result );
}

std::wstring FileSystem::GetDataFolder()
{
	return( data_folder_ );
}

std::wstring FileSystem::GetModelsFolder()
{
	return( data_folder_ + models_sub_folder_ );
}

std::wstring FileSystem::GetScriptsFolder()
{
	return( data_folder_ + scripts_sub_folder_ );
}

std::wstring FileSystem::GetShaderFolder()
{
	return( data_folder_ + shader_sub_folder_ );
}

std::wstring FileSystem::GetTextureFolder()
{
	return( data_folder_ + texture_sub_folder_ );
}

void FileSystem::SetDataFolder( const std::wstring& folder )
{
	data_folder_ = folder;
}

void FileSystem::SetModelsFolder( const std::wstring& folder )
{
	models_sub_folder_ = folder;
}

void FileSystem::SetScriptsFolder( const std::wstring& folder )
{
	scripts_sub_folder_ = folder;
}

void FileSystem::SetShaderFolder( const std::wstring& folder )
{
	shader_sub_folder_ = folder;
}

void FileSystem::SetTextureFolder( const std::wstring& folder )
{
	texture_sub_folder_ = folder;
}

bool FileSystem::FileExists( const std::wstring& file )
{
	// Check if the file exists, and that it is not a directory

	DWORD dwAttrib = GetFileAttributes( file.c_str() );

	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool FileSystem::FileIsNewer( const std::wstring& file1, const std::wstring& file2 )
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
    handle1 = CreateFileW( file1.c_str(),
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
    handle2 = CreateFileW( file2.c_str(),
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
