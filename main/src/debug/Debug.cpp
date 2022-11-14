//
// Created by Henry on 14/11/2022.
//

#include "../../include/debug/Debug.h"

namespace ConsoleGameEngine
{
	namespace Debug
	{
		Logger* logger;
		void InitLogger()
		{
			if(logger == nullptr)
				logger = new FileLogger("./debug.txt");
		}
		
		void Log(string msg)
		{
			InitLogger();
			logger->Log( msg);
		}
		
		void Warn(string msg)
		{
			InitLogger();
			logger->Warn( msg);
		}
		
		void Error(string msg)
		{
			InitLogger();
			logger->Error( msg);
		}
	} // ConsoleGameEngine
} // Debug