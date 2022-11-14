//
// Created by Henry on 14/11/2022.
//

#include "../../include/debug/FileLogger.h"

namespace ConsoleGameEngine
{
	namespace Debug
	{
		FileLogger::FileLogger(string filepath)
		{
			logFile.open(filepath);
			Log("Initialized log file.");
		}
		
		FileLogger::~FileLogger()
		{
			logFile.close();
		}
		
		void FileLogger::Log(string msg)
		{
			logFile << "Log : " << msg << std::endl;
		}
		
		void FileLogger::Warn(string msg)
		{
			logFile << "Warning : " << msg << std::endl;
		}
		
		void FileLogger::Error(string msg)
		{
			logFile << "Error : " << msg << std::endl;
		}
		
	}
} // ConsoleGameEngine