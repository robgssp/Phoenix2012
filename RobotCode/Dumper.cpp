#include "Dumper.h"

Dumper::Dumper(int frontRollerPort, int rearRollerPort, int infraPort,
		Robot *robot) {
	this->robot_ = robot;
	this->frontRoller_ = new Relay(frontRollerPort);
	this->rearRoller_ = new Relay(rearRollerPort);
	this->infra_ = new AnalogChannel(infraPort);
}

bool Dumper::full() {
	
}
