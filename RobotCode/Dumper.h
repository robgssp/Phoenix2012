#ifndef DUMPER_H
#define DUMPER_H
#include "WPILib.h"
#include "Robot.h"
#include <ctime>

class Dumper {
	Robot *robot_;
	DigitalInput *intakeSwitch_;
	CANJaguar *roller_;

	clock_t intakeEnd_;
	double powerNow_;
	double setPower(double power);
public:
	enum Direction { Reverse = -1, Off, Forward };
	Dumper(int rollerPort, int infraPort, Robot *robot);

	// intake
	void updateIntake();
	bool isIntaking();

	// raw
	void setDirection(Direction dir);
};

#endif
