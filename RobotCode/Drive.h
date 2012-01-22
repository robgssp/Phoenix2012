#ifndef PHOENIXDRIVE_H
#define PHOENIXDRIVE_H
#include "WPILib.h"
#include "Robot.h"
#include <vector>

struct MotorProperty {
	CANJaguar *motor;
	double defaultScale;
};

/**
 * Default robot drive doesn't implement scaling.
 * Reimplemented, though without arcade drive (never used anyways).
 */
class Drive {
	typedef std::vector<MotorProperty> MotorVector;
	void setMotors(const MotorVector &motors, double value);
	double motorVoltage(const MotorVector &motors);
	MotorVector leftMotors_;
	MotorVector rightMotors_;
	double scale_;
	bool reversed_;
	Robot *robot_;
	
public:
	enum Side { Left, Right };
	Drive(Robot *config);
	virtual ~Drive();
	void setLeft(double value);
	void setRight(double value);
	void setScale(double value);
	double leftVoltage();
	double rightVoltage();
	void setReversed(bool reversed);
	void addMotor(Side, CANJaguar *, double defaultScale);
	void updateLight();
};

#endif
