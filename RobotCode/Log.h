#ifndef LOG_H
#define LOG_H
#include "WPILib.h"
#include "Robot.h"
#include <string>

/**
 * wrapper for wpilib's bullshit default log facility.
 * Logs everything pushed to error, and info as well if there's room
 */
class Log {
	Robot *robot_;
	std::vector<std::string> info_;
	std::vector<std::string> error_;
	void printVec(std::vector<std::string> &vec, int &freeLines);
public:
	Log(Robot *robot);
	void info(std::string text, ...);
	void error(std::string text, ...);
	void print();
};

#endif
