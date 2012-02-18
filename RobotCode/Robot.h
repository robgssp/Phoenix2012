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
class Balance;
class Arm;
class Gatherer;

/** 
 * Container class for robot components
 */
class Robot {
public:	
	enum Type { BotProto, BotFinal };
	Robot(Type type);
	virtual ~Robot();
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
	Type type;
	Balance *balance;
	Solenoid *rampDevice;
	Arm *arm;
	Gatherer *gatherer;
};

#endif
