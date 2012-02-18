#include "BcdSwitch.h"
#include <cmath>

BcdSwitch::BcdSwitch(int port1, int port2, int port3, int port4) {
	this->ports[0] = new DigitalInput(port1);
	this->ports[1] = new DigitalInput(port2);
	this->ports[2] = new DigitalInput(port3);
	this->ports[3] = new DigitalInput(port4);
}

int BcdSwitch::value() {
	int ret = 15;
	for(int i = 0; i < 4; ++i) {
		if (ports[i]->Get()) ret -= (int) pow(2, i);
	}
	return ret;
}

bool BcdSwitch::valOne(int which) {
	return ports[which]->Get();
}

