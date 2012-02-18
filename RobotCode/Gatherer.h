#ifndef GATHERER_H_
#define GATHERER_H_
#include "WPILib.h"
#include "Robot.h"


class Gatherer {
	Robot *robot_;
	Relay *relay_;
public:
	Gatherer(int motorPort, Robot *robot);
	void setEnabled(bool enabled);
};

#endif
