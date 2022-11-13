//
// Created by Henry on 13/11/2022.
//

#ifndef CONSOLEGAMEENGINEPLUSPLUS_TESTCARTRIDGE_H
#define CONSOLEGAMEENGINEPLUSPLUS_TESTCARTRIDGE_H

#include "GameCartridge.h"

namespace ConsoleGameEngine
{
	class TestCartridge : public GameCartridge
	{
	public:
		void Inititialize();
		void Deinitialize();
		void Update(double deltaTime);
		void Render(Canvas& canvas);
	};
	
} // ConsoleGameEngine

#endif //CONSOLEGAMEENGINEPLUSPLUS_TESTCARTRIDGE_H
