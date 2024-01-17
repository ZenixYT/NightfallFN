#pragma once
#include <iostream>
#include <map>
#include "Hooks.hpp"

namespace Keybinds
{
	enum KEYBIND_TYPE
	{
		NONE,
		WALL, FLOOR, STAIR, PYRAMID, TRAP,
		SLOT_ONE, SLOT_TWO, SLOT_THREE, SLOT_FOUR, SLOT_FIVE, SLOT_SIX
	};

	namespace BindSettings
	{
		bool bShouldBind = false;
		std::string sTypeToBind = "NONE";
		//KEYBIND_TYPE kTypeToBind = KEYBIND_TYPE::NONE;
	}

	std::map<std::string, int> KeyBinds;

	void BindKey(std::string type, int keyCode)
	{
		auto it = KeyBinds.find(type);
		if (it != KeyBinds.end())
			it->second = keyCode;
		else
			KeyBinds.insert({ type, keyCode });
	}

	void InitializeKeybinds()
	{
		BindKey("BUILD_WALL", 0x46);
		BindKey("BUILD_FLOOR", 0x58);
		BindKey("BUILD_STAIR", 0x43);
		BindKey("BUILD_PYRAMID", 0x55);
		BindKey("BUILD_TRAP", 0x54);

		BindKey("SLOT_ONE", 0x51);
		BindKey("SLOT_TWO", VK_XBUTTON2);
		BindKey("SLOT_THREE", VK_XBUTTON1);
		BindKey("SLOT_FOUR", 0x31);
		BindKey("SLOT_FIVE", 0x34);
		BindKey("SLOT_SIX", 0x35);
	}

	int GetKeyFromKeybindType(std::string type)
	{
		auto it = KeyBinds.find(type);
		if (it != KeyBinds.end())
			return it->second;

		return -1;
	}
}