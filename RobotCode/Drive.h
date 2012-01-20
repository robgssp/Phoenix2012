#ifndef PHOENIXDRIVE_H
#define PHOENIXDRIVE_H
#include "WPILib.h"
#include "Config.h"
#include <vector>

struct MotorProperty {
	CANJaguar *motor;
	double defaultScale;
};

class Drive {
	typedef std::vector<MotorProperty> MotorVector;
	MotorVector leftMotors_;
	MotorVector rightMotors_;
	double scale_;
	bool reversed_;
	Config *config_;
	
public:
	enum Side { Left, Right };
	Drive(Config *config);
	virtual ~Drive();
	void setLeft(double value);
	void setRight(double value);
	void setScale(double value);
	void setReversed(bool reversed);
	void addMotor(Side, CANJaguar *, double defaultScale);
	void updateLight();
};

#endif
