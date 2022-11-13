//
// Created by Henry on 13/11/2022.
//

#ifndef CONSOLEGAMEENGINEPLUSPLUS_GAMECARTRIDGE_H
#define CONSOLEGAMEENGINEPLUSPLUS_GAMECARTRIDGE_H

#include "Canvas.h"
#include "GameConsole.h"

namespace ConsoleGameEngine
{
	class GameCartridge
	{
	public:
		void Inititialize();
		void Deinitialize();
		void Update(double deltaTime);
		void Render(Canvas& canvas);
		bool IsRunning();
		
	protected:
		void Quit();
		
	private:
		bool isRunning;
	};
}

#endif //CONSOLEGAMEENGINEPLUSPLUS_GAMECARTRIDGE_H
