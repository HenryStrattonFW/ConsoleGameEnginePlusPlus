//
// Created by Henry on 13/11/2022.
//

#ifndef CONSOLEGAMEENGINEPLUSPLUS_GAMECARTRIDGE_H
#define CONSOLEGAMEENGINEPLUSPLUS_GAMECARTRIDGE_H

#include "Canvas.h"
#include <string>

namespace ConsoleGameEngine
{
	class GameCartridge
	{
	public:
		void Inititialize();
		void Deinitialize();
		virtual std::string CartridgeName() = 0;
		virtual void Update(double deltaTimeMs) = 0;
		virtual void Render(Canvas& canvas) = 0;
		bool IsRunning();
		
	protected:
		virtual void OnInitialize() = 0;
		virtual void OnDeinitialize() = 0;
		void Quit();
		
	private:
		bool isRunning;
	};
}

#endif //CONSOLEGAMEENGINEPLUSPLUS_GAMECARTRIDGE_H
