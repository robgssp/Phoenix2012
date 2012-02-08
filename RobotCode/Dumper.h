#ifndef DUMPER_H
#define DUMPER_H
#include "Robot.h"

class Dumper {
	Robot *robot_;
	Relay *frontRoller_;
	Relay *rearRoller_;
	AnalogChannel *infra_;
	bool switchWasTriggered_;
	bool infraWasTriggered_;
public:
	Dumper(int frontRollerPort, int rearRollerPort, int infraPort, 
		   Robot *robot);
	
	bool full();
};

#endif
