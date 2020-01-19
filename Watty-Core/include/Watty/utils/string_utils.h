#pragma once
#include <string>
#include <sstream>
#include <vector>

namespace letc {
	static std::vector<std::string> split_string(const std::string& string, char delimeter) {
		std::vector<std::string> elems;
		std::stringstream ss(string);
		std::string item;
		while (std::getline(ss, item, delimeter)) {
			elems.push_back(item);
		}
		return elems;
	}


}