#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace Utils
{
	std::vector<std::string> splitString(std::string stringToSplit, char delimiter)
	{
		std::stringstream test("this_is_a_test_string");
		std::string segment;
		std::vector<std::string> seglist;

		while (std::getline(test, segment, delimiter))
		{
			seglist.push_back(segment);
		}

		return seglist;
	}
}