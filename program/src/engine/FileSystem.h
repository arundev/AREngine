#pragma once

#include <string>

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	bool OperatingOnVista();
	bool OperatingOnXP();

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

	static std::wstring sDataFolder;
	static std::wstring sModelsSubFolder;
	static std::wstring sScriptsSubFolder;
	static std::wstring sShaderSubFolder;
	static std::wstring sTextureSubFolder;
};
