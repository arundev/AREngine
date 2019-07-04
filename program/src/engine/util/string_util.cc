#include "image_util.h"

namespace engine {

	std::string StringReplace(const std::string& input, const std::string& find, const std::string& replaceWith) {
		std::string strOut(input);
		int curPos = 0;
		int pos;

		while ((pos = strOut.find(find, curPos)) != -1)
		{
			strOut.replace(pos, find.size(), replaceWith);
			curPos = pos + replaceWith.size();
		}

		return strOut;
	}

	std::string FormatFilePath(const std::string& input)
	{
		std::string temp(input);
		temp = engine::StringReplace(temp, "\\", "/");
		temp = engine::StringReplace(temp, "//", "/");

		return temp;
	}

	std::string GetFileBaseName(const std::string& filePath)
	{
		std::string fileExtension;
		size_t pos = filePath.find_last_of("/\\");
		if (pos != std::string::npos)
		{
			return filePath.substr(pos + 1);
		}

		return filePath;
	}

	std::string GetFileNameWithoutExtension(const std::string& filePath)
	{
		std::string fileExtension;
		size_t pos = filePath.find_last_of('.');
		if (pos != std::string::npos)
		{
			return filePath.substr(0, pos);
		}
		return filePath;
	}


	std::string GetFileBaseNameWithoutExtension(const std::string& filePath)
	{
		std::string baseName = GetFileBaseName(filePath);
		return GetFileNameWithoutExtension(baseName);
	}
}