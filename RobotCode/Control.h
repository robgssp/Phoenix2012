#ifndef CONTROL_H
#define CONTROL_H
#include "WPILib.h"

class Control {
	Joystick *left_, *right_;
	double leftScale_, rightScale_;
	bool wasReversedPressed_;
	bool isReversed_;
	bool wasBridgeDeviceOnOffPressed_;
	bool wasBridgeDeviceUpDownPressed_;
	bool isBridgeDeviceOnOff_;
	bool isBridgeDeviceUpDown_;
public:
	enum Mode { Tank, Arcade };
	Control(Joystick *left, Joystick *right, Mode mode);
	virtual ~Control();
	void setLeftScale(double scale);
	void setRightScale(double scale);
	double left();
	double right();
	double throttle();
	bool isReversed();
	bool isBalancing(); // Activation for balancing (Hold button 5)
	bool button(int num);
	bool bridgeDeviceUpDown();
};

#endif
