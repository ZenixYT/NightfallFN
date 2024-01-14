#pragma once
#include <iostream>
#include <thread>
#include <Windows.h>
#include <functional>
//#include "Utils.h"

class NightfallCheat
{
public:
	std::atomic<bool> stopFlag{ false };
	bool bIsCheatEnabled = false;
	long long threadWaitTime;

	NightfallCheat(std::function<void()> cheatFunc, long long threadWaitTime = 10)
	{
		this->cheatFunc = cheatFunc;
		this->threadWaitTime = threadWaitTime;
	}

	void StartCheat()
	{
		stopFlag.store(false);

		if (!cheatThread.joinable())
		{
			cheatThread = std::thread([this]() { cheatThreadFunc(&stopFlag, cheatFunc, threadWaitTime); });
		}

		bIsCheatEnabled = true;

		cheatThread.detach();
	}

	void StopCheat()
	{
		stopFlag.store(true);
		bIsCheatEnabled = false;
	}
private:
	std::function<void()> cheatFunc;

	void cheatThreadFunc(std::atomic<bool>* stopFlag, std::function<void()> cheatFunc, long long threadWaitTime)
	{
		while (!stopFlag->load())
		{
			//if (Utils::IsFortniteFocused())
			//	cheatFunc();
			cheatFunc();
			std::this_thread::sleep_for(std::chrono::milliseconds(threadWaitTime));
		}
	}

	std::thread cheatThread;
};