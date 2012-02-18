#include "Control.h"
#include "Log.h"

Control::Control(Joystick *left, Joystick *right, Mode mode, Robot *robot)
	: isTriggered_(11, false), wasTriggered_(11, false) {
	this->left_ = left;
	this->right_ = right;
	control_ = right_;
	this->robot_ = robot;
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
	return (1 - control_->GetRawAxis(3)) / 2;
}

bool Control::isBalancing() {
	return button(2);
}

/// returns true while button is held
bool Control::button(int num) { return control_->GetRawButton(num); }

/// switches between true and false on button down
bool Control::toggleButton(int num) {
	try {
		bool isPressed = button(num);
		if(isPressed && !wasTriggered_[num])
			isTriggered_.at(num) = !isTriggered_.at(num);

		wasTriggered_.at(num) = isPressed;
		return isTriggered_.at(num);
	} catch (...) {
		robot_->log->info("Button switching failed");
		return false;
	}
}

