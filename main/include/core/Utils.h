//
// Created by Henry on 13/11/2022.
//

#ifndef CONSOLEGAMEENGINEPLUSPLUS_UTILS_H
#define CONSOLEGAMEENGINEPLUSPLUS_UTILS_H

#include "Colours.h"
#include "Canvas.h"
#include <string>

namespace ConsoleGameEngine
{
	namespace Utils
	{
		ForegroundColour RandomForeground();
		BackgroundColour RandomBackground();
		void DrawTextCentered(Canvas& canvas, short y, std::string text, ForegroundColour colour);
	} //Utils
	
} // ConsoleGameEngine

#endif //CONSOLEGAMEENGINEPLUSPLUS_UTILS_H
