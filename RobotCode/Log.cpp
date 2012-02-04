#include "Log.h"

static const DriverStationLCD::Line lines[] = {
		DriverStationLCD::kUser_Line1,
		DriverStationLCD::kUser_Line2,
		DriverStationLCD::kUser_Line3,
		DriverStationLCD::kUser_Line4,
		DriverStationLCD::kUser_Line5,
		DriverStationLCD::kUser_Line6
};

Log::Log(Robot *robot) {
	this->robot_ = robot;
}

void Log::info(const char *text, ...) { 
	char buf[100];
	buf[99] = '\0';
	va_list vl;
	va_start(vl, text);
	vsnprintf(buf, 100, text, vl);
	info_.push_back(std::string(buf)); 
}

void Log::error(const char *text, ...) { 
	char buf[100];
	buf[99] = '\0';
	va_list vl;
	va_start(vl, text);
	vsnprintf(buf, 100, text, vl);
	error_.push_back(std::string("e:") + std::string(buf)); 
}

void Log::print() {
	int line = 0;
	printVec(error_, line);
	printVec(info_, line);
	robot_->lcd->UpdateLCD();
}

void Log::printVec(std::vector<std::string> &vec, int &line) {
	std::vector<std::string>::iterator iter;
	for(iter = vec.begin(); iter != vec.end(); ++iter) {
		if(line == 6) { 
			robot_->lcd->PrintfLine(lines[5], "...more...");
			break;
		}
		robot_->lcd->PrintfLine(lines[line], "%s", (*iter).c_str());
		++line;
	}
	vec.clear();
}
