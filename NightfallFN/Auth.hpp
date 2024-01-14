#pragma once
#include <Windows.h>
#include <iostream>

namespace Auth
{
	std::string sCorrectKey = "nightfall-faggot-tranny";
	bool checkKey(std::string keyToCheck)
	{
		if (keyToCheck == sCorrectKey)
			return true;
		return false;
	}

	void promptKey()
	{
		std::string sKeyToCheck;
		std::cout << "Enter key: ";
		std::cin >> sKeyToCheck;
		if (!checkKey(sKeyToCheck))
			promptKey();
	}
}