#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace Utils
{
	std::vector<std::string> splitString(std::string s, char delimiter)
	{
        std::vector<std::string> tokens;
        size_t start = 0, end = 0;
        while ((end = s.find(delimiter, start)) != std::string::npos) {
            tokens.push_back(s.substr(start, end - start));
            start = end + 1;
        }
        tokens.push_back(s.substr(start));
        return tokens;
	}
}