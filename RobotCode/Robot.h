#ifndef CONFIG_H
#define CONFIG_H
#include "WPILib.h"
#include <vector>

class Control;
class Drive;
class Autonomous;
class BcdSwitch;
class ImageTracker;
class Log;

/** 
 * Container class for robot components
 */
class Robot {
public:	
	enum Type { BotProto, BotFinal };
	Robot(Type type);
	virtual ~Robot();
	DriverStationLCD *lcd;
	Drive *drive;
	Control *control;
	Relay *driveLight;
	AnalogChannel *ultrasonic;
	Autonomous *autonomous;
	AnalogChannel *gyroChannel;
	Gyro *gyro;
	DigitalInput *touchSensor;
	AxisCamera *camera;
	BcdSwitch *bcd;
	ImageTracker *imageTracker;
	Log *log;
	Compressor *compressor;
private:
	Type type_;
};

#endif
