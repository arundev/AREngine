#ifndef ENGINE_UTIL_STRING_H
#define ENGINE_UTIL_STRING_H

#include <iostream>
#include <vector>

namespace engine_util {
	inline std::string StringTrim(const std::string& str) {
		std::string::size_type pos = str.find_first_not_of(' ');
		if (pos == std::string::npos) {
			return str;
		}
		std::string::size_type pos2 = str.find_last_not_of(' ');
		if (pos2 != std::string::npos) {
			return str.substr(pos, pos2 - pos + 1);
		}
		return str.substr(pos);
	}

	inline int StringSplit(const std::string& str, std::vector<std::string>& ret_, std::string sep = ",") {
		if (str.empty()) {
			return 0;
		}

		std::string tmp;
		std::string::size_type pos_begin = str.find_first_not_of(sep);
		std::string::size_type comma_pos = 0;

		while (pos_begin != std::string::npos) {
			comma_pos = str.find(sep, pos_begin);
			if (comma_pos != std::string::npos) {
				tmp = str.substr(pos_begin, comma_pos - pos_begin);
				pos_begin = comma_pos + sep.length();
			}
			else {
				tmp = str.substr(pos_begin);
				pos_begin = comma_pos;
			}

			if (!tmp.empty()) {
				ret_.push_back(tmp);
				tmp.clear();
			}
		}
		return 0;
	}

	inline std::string StringReplace(const std::string& str, const std::string& src, const std::string& dest) {
		std::string ret;

		std::string::size_type pos_begin = 0;
		std::string::size_type pos = str.find(src);
		while (pos != std::string::npos) {
			std::cout << "replacexxx:" << pos_begin << " " << pos << "\n";
			ret.append(str.data() + pos_begin, pos - pos_begin);
			ret += dest;
			pos_begin = pos + 1;
			pos = str.find(src, pos_begin);
		}
		if (pos_begin < str.length()) {
			ret.append(str.begin() + pos_begin, str.end());
		}
		return ret;
	}
}


#endif // ENGINE_UTIL_STRING_H