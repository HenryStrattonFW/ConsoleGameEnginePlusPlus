//
// Created by Henry on 13/11/2022.
//
#include "../include/GameCartridge.h"

namespace ConsoleGameEngine
{
	void GameCartridge::Inititialize()
	{
		isRunning = true;
	}
	
	void GameCartridge::Quit()
	{
		isRunning = false;
	}
	
	bool GameCartridge::IsRunning()
	{
		return isRunning;
	}
	
}//ConsoleGameEngine
