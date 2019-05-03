#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Logger.h"

Logger::Logger(int log_level)
{
	CurrentLogLevel = log_level;
}

void Logger::ChangeLogLevel(int log_level)
{
	/* Change log level (default is Info)*/
	CurrentLogLevel = log_level;
}

void Logger::log(const char* message, int log_level)
{
	/* Writing const char* log message with specified log_level to console */
	if (log_level >= CurrentLogLevel)
	{
		if (log_level == Info)
		{
			std::cout << "[Info]: " << message << std::endl;
		}
		else if (log_level == Warning)
		{
			std::cout << "[Warning]: " << message << std::endl;
		}
		else
		{
			std::cout << "[Error]: " << message << std::endl;
		}
	}
}

void Logger::log(int digit, int log_level)
{
	/* Writing int log message with specified log_level to console */
	if (log_level >= CurrentLogLevel)
	{
		if (log_level == Info)
		{
			std::cout << "[Info]: " << digit << std::endl;
		}
		else if (log_level == Warning)
		{
			std::cout << "[Warning]: " << digit << std::endl;
		}
		else
		{
			std::cout << "[Error]: " << digit << std::endl;
		}
	}
}
