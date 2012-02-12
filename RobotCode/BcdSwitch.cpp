#include "BcdSwitch.h"

BcdSwitch::BcdSwitch(int port1, int port2, int port3) {
	this->port1 = new DigitalInput(port1);
	this->port2 = new DigitalInput(port2);
	this->port3 = new DigitalInput(port3);
}

int BcdSwitch::value() {
	int ret;
	if (!port1->Get()) ret += 1;
	if (!port2->Get()) ret += 2;
	if (!port3->Get()) ret += 4;
	return ret;
}
