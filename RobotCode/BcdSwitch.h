#ifndef BCDSWITCH_H
#define BCDSWITCH_H
#include "WPILib.h"

class BcdSwitch {
	DigitalInput *port1, *port2;
public:
	BcdSwitch(int port1, int port2);
	int value();
};

#endif
