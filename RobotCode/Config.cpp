#include "Config.h"

std::vector<int> ProtoConfig::leftMotors() {
	int motors[] = {2, 3};
	return std::vector<int>(motors, motors + sizeof(motors) / sizeof(motors[0]));
}

std::vector<int> ProtoConfig::rightMotors() {
	int motors[] = {6, 7};
	return std::vector<int>(motors, motors + sizeof(motors) / sizeof(motors[0]));
}
