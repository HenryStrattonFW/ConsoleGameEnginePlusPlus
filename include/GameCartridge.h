//
// Created by Henry on 13/11/2022.
//

#ifndef CONSOLEGAMEENGINEPLUSPLUS_GAMECARTRIDGE_H
#define CONSOLEGAMEENGINEPLUSPLUS_GAMECARTRIDGE_H

#include "Canvas.h"

namespace ConsoleGameEngine
{
	class GameCartridge
	{
	public:
		void Inititialize();
		virtual void Deinitialize() = 0;
		virtual void Update(double deltaTime) = 0;
		virtual void Render(Canvas& canvas) = 0;
		bool IsRunning();
		
	protected:
		void Quit();
		
	private:
		bool isRunning;
	};
}

#endif //CONSOLEGAMEENGINEPLUSPLUS_GAMECARTRIDGE_H
