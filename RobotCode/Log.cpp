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

void Log::info(std::string text, ...) { 
	char buf[100];
	va_list vl;
	va_start(vl, text);
	vsnprintf(buf, 100, text.c_str(), vl);
	info_.push_back(std::string(buf, 100)); 
}

void Log::error(std::string text, ...) { 
	char buf[100];
	va_list vl;
	va_start(vl, text);
	vsnprintf(buf, 100, text.c_str(), vl);
	error_.push_back(std::string(buf, 100)); 
}

void Log::print() {
	int freeLines = 6;
	printVec(error_, freeLines);
	printVec(info_, freeLines);
}

void Log::printVec(std::vector<std::string> &vec, int &freeLines) {
	if(freeLines < 1) return;
	
	for(size_t i = 0; i < vec.size(); ++i) {
		if(freeLines == 1) {
			robot_->lcd->PrintfLine(lines[5], "...more...");
			break;
		}
		
		robot_->lcd->PrintfLine(lines[6 - freeLines--], vec[i].c_str());
	}
	vec.clear();
}
