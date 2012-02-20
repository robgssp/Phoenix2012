#ifndef DUMPER_H
#define DUMPER_H
#include "WPILib.h"
#include "Robot.h"
#include <ctime>

class Dumper {
	Robot *robot_;
	DigitalInput *intakeSwitch_;

	clock_t intakeEnd_;
public:
	Dumper(int rollerPort, int infraPort, Robot *robot);
	// deployment
	void setDeploy(bool enabled);
	Relay *roller_;

	// intake
	void updateIntake();
	bool isIntaking();

	// raw
	void setDirection(Relay::Value dir);
};

#endif
