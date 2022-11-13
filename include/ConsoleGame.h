//
// Created by Henry on 13/11/2022.
//

#ifndef CONSOLEGAMEENGINEPLUSPLUS_CONSOLEGAME_H
#define CONSOLEGAMEENGINEPLUSPLUS_CONSOLEGAME_H

#include <Windows.h>
#include "Canvas.h"
#include <string>
using namespace std;

namespace ConsoleGameEngine
{
	class ConsoleGame
	{
	private:
		HANDLE writeHandle;
		HANDLE readHandle;
		COORD screenSize;
		SMALL_RECT screenRect;
		Canvas* activeCanvas;
		Canvas* presentedCanvas;
		bool gameActive;
		void UpdateInput();
	
	public:
		ConsoleGame(string name, short width, short height);
		~ConsoleGame();
		
		void Update();
		void Render();
		void Quit();
		
		Canvas& GetCanvas();
		bool IsGameActive();
	};
} // ConsoleGameEngine

#endif //CONSOLEGAMEENGINEPLUSPLUS_CONSOLEGAME_H
