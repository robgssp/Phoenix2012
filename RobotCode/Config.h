#ifndef CONFIG_H
#define CONFIG_H
#include "WPILib.h"
#include <vector>

class Control;
class Drive;
class Autonomous;

class Config {
public:	
	std::vector<CANJaguar *> leftMotors();
	std::vector<CANJaguar *> rightMotors();
	DriverStationLCD *lcd;
	Drive *drive;
	Control *control;
	Relay *driveLight;
	AnalogChannel *ultrasonic;	
	Autonomous *autonomous;
};

#endif
