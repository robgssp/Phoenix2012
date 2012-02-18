#ifndef BCDSWITCH_H
#define BCDSWITCH_H
#include "WPILib.h"

class BcdSwitch {
	DigitalInput *ports[4];
public:
	BcdSwitch(int port1, int port2, int port3, int port4);
	int value();
	bool valOne(int which);
};

#endif
