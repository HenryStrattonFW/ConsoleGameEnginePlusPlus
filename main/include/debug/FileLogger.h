//
// Created by Henry on 14/11/2022.
//

#ifndef CONSOLEGAMEENGINEPLUSPLUS_FILELOGGER_H
#define CONSOLEGAMEENGINEPLUSPLUS_FILELOGGER_H

#include "Logger.h"
#include <iostream>
#include <fstream>

namespace ConsoleGameEngine
{
	namespace Debug
	{
		class FileLogger : public Logger
		{
		public:
			FileLogger(string filepath);
			~FileLogger();
			
			void Log(string msg);
			void Warn(string msg);
			void Error(string msg);
		
		private:
			std::ofstream logFile;
		};
		
	} // Debug
} // ConsoleGameEngine

#endif //CONSOLEGAMEENGINEPLUSPLUS_FILELOGGER_H
