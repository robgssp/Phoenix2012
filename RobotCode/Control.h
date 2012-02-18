#ifndef CONTROL_H
#define CONTROL_H
#include "WPILib.h"
#include "Robot.h"
#include <vector>

class Control {
	Joystick *left_, *right_;

	// joystick to get button presses
	Joystick *control_;
	double leftScale_, rightScale_;

	std::vector<bool> isTriggered_;
	std::vector<bool> wasTriggered_;

	Robot *robot_;

	bool wasBridgeDeviceOnOffPressed_;
	bool wasBridgeDeviceUpDownPressed_;
	bool isBridgeDeviceOnOff_;
	bool isBridgeDeviceUpDown_;
public:
	enum Mode { Tank, Arcade };
	Control(Joystick *left, Joystick *right, Mode mode, Robot *robot);
	virtual ~Control();
	void setLeftScale(double scale);
	void setRightScale(double scale);
	double left();
	double right();
	double throttle();
	bool isReversed();
	bool isBalancing(); // Activation for balancing (Hold button 5)
	bool button(int num);
	bool toggleButton(int num);
	bool bridgeDeviceUpDown();
};

#endif
