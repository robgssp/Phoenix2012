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
	MotorVector leftMotors_;
	MotorVector rightMotors_;
	void setMotors(const MotorVector &motors, double value);
	double motorCurrent(const MotorVector &motors);
	double scale_;
	bool reversed_;
	Robot *robot_;
	Solenoid *shifter_;
	
	// update state
	void updateLight();
	
public:
	enum Side { Left, Right };
	Drive(int shifterPort, Robot *config);
	Drive(Robot *config);
	virtual ~Drive();
	
	// power ctl
	void setLeft(double value);
	void setRight(double value);
	
	// scaling
	void setScale(double value);
	void setReversed(bool reversed);
	
	// current
	double leftCurrent();
	double rightCurrent();
	double current();
	
	// shift
	enum ShiftMode { Manual = 1, Automatic };
	void setShiftMode(ShiftMode mode);
	void setLowShift(bool set);
	void updateShifter();
	
	// configuration
	void addMotor(Side, int port, double defaultScale);
	
private:
	ShiftMode mode_;
};

#endif
