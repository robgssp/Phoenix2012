#ifndef BCDSWITCH_H
#define BCDSWITCH_H
#include "WPILib.h"

class BcdSwitch {
	DigitalInput *port1, *port2, *port3;
public:
	BcdSwitch(int port1, int port2, int port3);
	int value();
};

#endif
