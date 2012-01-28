#include "BcdSwitch.h"

BcdSwitch::BcdSwitch(int port1, int port2) {
	this->port1 = new DigitalInput(port1);
	this->port2 = new DigitalInput(port2);
}

int BcdSwitch::value() {
	int value;
	if (!port1->Get())
		value += 1;
	if (!port2->Get())
		value += 2;
	return value;
}
