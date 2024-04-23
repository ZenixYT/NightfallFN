#pragma once
#include <nlohmann/json.hpp>
#include <iostream>
#include "CheatManager.hpp"

namespace JSONParser
{

	void ParseJSON(std::string json)
	{
		nlohmann::json pJSON = nlohmann::json::parse(json);

		// First, let's make sure it has an associated module
		std::string cheatModule = pJSON["module"];
		auto changesArray = pJSON["changes"];

		// dont do what im bout to do, you wanna do a switch statement
		if (cheatModule == "noRecoil")
		{
			for (const auto& change : changesArray)
			{
				std::string setting = change["setting"];
				if (setting == "recoilMagnitude")
				{
					int value = change["value"];
					recoilMag = (DWORD)value;
					std::cout << recoilMag << std::endl;
				}
				/*else if (setting == "isEnabled")
				{
					auto value = change["value"];
					std::cout << value << std::endl;
				}*/
			}
		}
	}
}