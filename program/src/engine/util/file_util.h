#ifndef ENGINE_FILE_SYSTEM_H
#define ENGINE_FILE_SYSTEM_H

#include "../engine_pch.h"
#include <string>

namespace engine {


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
	std::string GetConfigFolder();

	void SetDataFolder(const std::string& folder);
	void SetModelsFolder(const std::string& folder);
	void SetScriptsFolder(const std::string& folder);
	void SetShaderFolder(const std::string& folder);
	void SetTextureFolder(const std::string& folder);
	void SetConfigFolder(const std::string& folder);

	static bool FileExists(const std::string& file);
	bool FileIsNewer(const std::string& file1, const std::string& file2);

	static std::string getDirectory(const std::string& path);
	static std::string getFileName(const std::string& path);
	static std::string getFileNameWithoutExtension(const std::string& path);

private:
	std::string data_folder_;
	std::string models_sub_folder_;
	std::string scripts_sub_folder_;
	std::string shader_sub_folder_;
	std::string texture_sub_folder_;
	std::string config_sub_folder_;
};


}
#endif // FILE_SYSTEM_H