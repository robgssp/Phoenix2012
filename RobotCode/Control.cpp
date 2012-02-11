#include "Control.h"

Control::Control(Joystick *left, Joystick *right, Mode mode) {
	this->left_ = left;
	this->right_ = right;
	wasReversedPressed_ = isReversed_ = false;
}

Control::~Control() {
	delete left_;
	delete right_;
}

void Control::setLeftScale(double scale) {
	leftScale_ = scale;
}

void Control::setRightScale(double scale) {
	rightScale_ = scale;
}

double Control::left() {
	return left_->GetY() * leftScale_;
}

double Control::right() {
	return right_->GetY() * rightScale_;
}

double Control::throttle() {
	return (1 - left_->GetRawAxis(3)) / 2;
}

bool Control::isReversed() {
	bool isReversedPressed = button(3);
	if(isReversedPressed && !wasReversedPressed_) {
		isReversed_ = !isReversed_;
	} 
	wasReversedPressed_ = isReversedPressed;
	return isReversed_;
}

bool Control::isBalancing() {
	return button(2);
}

bool Control::button(int num) {
	return right_->GetRawButton(num);
}

bool Control::bridgeDeviceUpDown() {
	bool isBridgeDeviceUpDownPressed = button(5);
	if (isBridgeDeviceUpDownPressed && !wasBridgeDeviceUpDownPressed_) {
		isBridgeDeviceUpDown_ = !isBridgeDeviceUpDown_;
	}
	wasBridgeDeviceUpDownPressed_ = isBridgeDeviceUpDownPressed;
	return isBridgeDeviceOnOff_;
}
