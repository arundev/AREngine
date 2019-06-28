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
	temp = engine::StringReplace(input, "\\", "/");
	temp = engine::StringReplace(input, "//", "/");

	return temp;
}

}