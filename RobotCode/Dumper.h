#ifndef DUMPER_H
#define DUMPER_H
#include "Robot.h"

struct IntakeState;

class Dumper {
	Robot *robot_;
	Relay *frontRoller_;
	Relay *rearRoller_;
	AnalogChannel *infra_;
	bool switchWasTriggered_;
	bool infraWasTriggered_;
	
	// for deployOne()
	void setDeployTarget();

	// for intake()
	IntakeState *intake_;
public:
	Dumper(int frontRollerPort, int rearRollerPort, int infraPort, 
		   Robot *robot);
	
	int contains();
	
	// deployment
	void deploy();
	bool deployOne();

	// intake
	void intake();
};

#endif
