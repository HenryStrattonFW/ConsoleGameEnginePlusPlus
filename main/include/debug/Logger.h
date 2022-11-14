//
// Created by Henry on 14/11/2022.
//

#ifndef CONSOLEGAMEENGINEPLUSPLUS_LOGGER_H
#define CONSOLEGAMEENGINEPLUSPLUS_LOGGER_H

#include <string>
using namespace std;

namespace ConsoleGameEngine
{
	namespace Debug
	{
		
		class Logger
		{
		public:
			virtual void Log(string msg) = 0;
			virtual void Warn(string msg) = 0;
			virtual void Error(string msg) = 0;
		};
		
	} // Debug
	
}// ConsoleGameEngine

#endif //CONSOLEGAMEENGINEPLUSPLUS_LOGGER_H
