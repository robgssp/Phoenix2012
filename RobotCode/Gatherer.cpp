#include "Gatherer.h"

Gatherer::Gatherer(int gatherPort, Robot *robot) {
	this->robot_ = robot;
	this->relay_ = new Relay(gatherPort);
}

void Gatherer::setDirection(Relay::Value dir) {
	relay_->Set(dir);
}

