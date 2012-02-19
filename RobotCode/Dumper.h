#ifndef DUMPER_H
#define DUMPER_H
#include "WPILib.h"
#include "Robot.h"
#include <ctime>

class Dumper {
	Robot *robot_;
	Relay *roller_;
	DigitalInput *intakeSwitch_;

	clock_t intakeEnd_;
public:
	Dumper(int rollerPort, int infraPort, Robot *robot);
	// deployment
	void deploy();

	// intake
	void updateIntake();
};

#endif
