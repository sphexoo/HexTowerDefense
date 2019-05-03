#pragma once

class Logger
{
public:
	int CurrentLogLevel = Error;

	enum log_level
	{
		Info = 1,
		Warning = 2,
		Error = 3
	};

	Logger(int log_level);
	void ChangeLogLevel(int log_level);
	void log(const char* message, int log_level);
	void log(int digit, int log_level);
};