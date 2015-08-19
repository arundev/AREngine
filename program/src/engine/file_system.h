#ifndef ENGINE_FILE_SYSTEM_H
#define ENGINE_FILE_SYSTEM_H

#include <string>

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	std::wstring GetLogFolder();
		
	std::wstring GetDataFolder();
	std::wstring GetModelsFolder();
	std::wstring GetScriptsFolder();
	std::wstring GetShaderFolder();
	std::wstring GetTextureFolder();

	void SetDataFolder( const std::wstring& folder );
	void SetModelsFolder( const std::wstring& folder );
	void SetScriptsFolder( const std::wstring& folder );
	void SetShaderFolder( const std::wstring& folder );
	void SetTextureFolder( const std::wstring& folder );

	bool FileExists( const std::wstring& file );
	bool FileIsNewer( const std::wstring& file1, const std::wstring& file2 );

private:
	static std::wstring data_folder_;
	static std::wstring models_sub_folder_;
	static std::wstring scripts_sub_folder_;
	static std::wstring shader_sub_folder_;
	static std::wstring texture_sub_folder_;
};

#endif // FILE_SYSTEM_H