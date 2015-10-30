#ifndef ENGINE_FILE_SYSTEM_H
#define ENGINE_FILE_SYSTEM_H

#include "../engine_pch.h"
#include <string>

class FileUtil
{
public:
	FileUtil();
	~FileUtil();

	bool Init() { return true; }
	void Update() { ;}
	void Free() { ; }

	std::string GetLogFolder();
		
	std::string GetDataFolder();
	std::string GetModelsFolder();
	std::string GetScriptsFolder();
	std::string GetShaderFolder();
	std::string GetTextureFolder();

	void SetDataFolder(const std::string& folder);
	void SetModelsFolder(const std::string& folder);
	void SetScriptsFolder(const std::string& folder);
	void SetShaderFolder(const std::string& folder);
	void SetTextureFolder(const std::string& folder);

	static bool FileExists(const std::string& file);
	bool FileIsNewer(const std::string& file1, const std::string& file2);

private:
	std::string data_folder_;
	std::string models_sub_folder_;
	std::string scripts_sub_folder_;
	std::string shader_sub_folder_;
	std::string texture_sub_folder_;
	std::string config_sub_folder_;
};

#endif // FILE_SYSTEM_H