//
// Created by Henry on 14/11/2022.
//

#ifndef CONSOLEGAMEENGINEPLUSPLUS_DEBUG_H
#define CONSOLEGAMEENGINEPLUSPLUS_DEBUG_H

#include "../../include/debug/FileLogger.h"

namespace ConsoleGameEngine
{
	namespace Debug
	{
		void Log(string msg);
		void Warn(string msg);
		void Error(string msg);
		
	} // ConsoleGameEngine
} // Debug

#endif //CONSOLEGAMEENGINEPLUSPLUS_DEBUG_H
