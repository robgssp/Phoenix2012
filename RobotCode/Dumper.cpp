#include "Dumper.h"

Dumper::Dumper(int rollerPort, int switchPort, Robot *robot) {
	this->robot_ = robot;
	this->roller_ = new Relay(rollerPort);
	//this->intakeSwitch_ = new DigitalInput(switchPort);
	intakeEnd_ = -1;
}

/**
 * Runs dumper motors in deployment mode
 */
void Dumper::setDeploy(bool enabled) {
	roller_->Set(enabled ? Relay::kForward : Relay::kOff);
}

/// not in seconds since TICKS_PER_SECOND is broken
static const clock_t intakeTime = 50;

void Dumper::updateIntake() {
	clock_t now = clock();
	if (intakeEnd_ == -1) {
		if(intakeSwitch_->Get()) {
			intakeEnd_ = now + intakeTime;
		} else {
			return;
		}
	} else if (intakeEnd_ <= now) {
		intakeEnd_ = -1;
		roller_->Set(Relay::kReverse);
		return;
	}
}

bool Dumper::isIntaking() {
	return intakeEnd_ == -1;
}

void Dumper::setDirection(Relay::Value dir) {
	roller_->Set(dir);
}
