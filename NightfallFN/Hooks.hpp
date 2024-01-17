#pragma once
#include <Windows.h>

namespace Hooks
{
	HHOOK keyboardHook;
	HHOOK mouseHook;

	LRESULT CALLBACK LowLevelKeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		//TODO: Write keybind code here
		
		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}

	LRESULT CALLBACK LowLevelMouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		//TODO: Write keybind code here (for mouse)

		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}

	void SetupHooks()
	{
		keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardHookProc, 0, 0);
		mouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseHookProc, 0, 0);
	}

	void UnhookHooks()
	{
		UnhookWindowsHookEx(keyboardHook);
		UnhookWindowsHookEx(mouseHook);
	}
}