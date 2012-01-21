#include "Robot.h"

std::vector<CANJaguar *> Robot::leftMotorIds() {
	std::vector<CANJaguar *> motors;
	int motorIds[] = {2, 3};
	for(int i = 0; i < 2; ++i) 
		motors.push_back(new CANJaguar(motorIds[i]));
	return motors;
}

std::vector<CANJaguar *> Robot::rightMotorIds() {
	std::vector<CANJaguar *> motors;
	int motorIds[] = {6, 7};
	for(int i = 0; i < 2; ++i) 
		motors.push_back(new CANJaguar(motorIds[i]));
	return motors;
}
