//
// Created by Henry on 13/11/2022.
//

#ifndef CONSOLEGAMEENGINEPLUSPLUS_GAMECONSOLE_H
#define CONSOLEGAMEENGINEPLUSPLUS_GAMECONSOLE_H

#include <Windows.h>
#include <string>
#include "Canvas.h"
#include "GameCartridge.h"

using namespace std;

namespace ConsoleGameEngine
{
	class GameConsole
	{
	public:
		GameConsole(string name, short width, short height);
		~GameConsole();
		
		void Run(GameCartridge &cartridge);
		
	private:
		void Update();
		void Render();
		
		HANDLE writeHandle;
		HANDLE readHandle;
		COORD screenSize;
		SMALL_RECT screenRect;
		Canvas* activeCanvas;
		Canvas* presentedCanvas;
	};
} // ConsoleGameEngine

#endif //CONSOLEGAMEENGINEPLUSPLUS_GAMECONSOLE_H
