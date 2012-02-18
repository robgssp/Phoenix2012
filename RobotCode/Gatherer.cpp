#include "Gatherer.h"

Gatherer::Gatherer(int gatherPort, Robot *robot) {
	this->robot_ = robot;
	this->relay_ = new Relay(gatherPort);
}

void Gatherer::setEnabled(bool enabled) {
	relay_->Set(enabled ? Relay::kReverse : Relay::kOff);
}

