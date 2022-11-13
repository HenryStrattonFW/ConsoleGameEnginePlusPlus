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
		void OnInitialize();
		void OnDeinitialize();
		void Update(double deltaTimeMs);
		void Render(Canvas& canvas);
		
	private:
		void RefreshNested();
		Canvas* nestedCanvas;
	};
	
} // ConsoleGameEngine

#endif //CONSOLEGAMEENGINEPLUSPLUS_TESTCARTRIDGE_H
