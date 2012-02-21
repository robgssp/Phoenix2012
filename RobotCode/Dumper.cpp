#include "Dumper.h"
#include "Log.h"
#include <algorithm>
using namespace std;

Dumper::Dumper(int rollerPort, int switchPort, Robot *robot) {
	this->robot_ = robot;
	this->roller_ = new CANJaguar(rollerPort);
	//this->intakeSwitch_ = new DigitalInput(switchPort);
	intakeEnd_ = -1;
	powerNow_ = 0;
}

/**
 * Runs dumper motors
 */
void Dumper::setDirection(Direction dir) {
	switch (dir) {
		case Reverse:
			setPower(powerNow_ +
					(roller_->GetOutputCurrent() < 25 ? -0.1 : 0.1));
			break;
		case Off:
			setPower(0);
			break;
		case Forward:
				setPower(powerNow_ + 
						(roller_->GetOutputCurrent() < 25 ? 0.1 : -0.1));
			break;
		default:
			robot_->log->info("Direction failed.");
			break;
	}
	robot_->log->info("Amps: %f, %d", roller_->GetOutputCurrent(), dir);
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

double Dumper::setPower(double power) {
	double outPower = powerNow_ = min(1, max(-1, power));
	roller_->Set(outPower);
	return outPower;
}
