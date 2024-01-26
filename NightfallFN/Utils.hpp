#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace Utils
{
	std::vector<std::string> splitString(std::string stringToSplit, char delimiter)
	{
		std::stringstream test(stringToSplit);
		std::string segment;
		std::vector<std::string> seglist;

		while (std::getline(test, segment, delimiter))
		{
			seglist.push_back(segment);
		}

		return seglist;
	}
}