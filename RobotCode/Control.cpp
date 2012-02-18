#include "Control.h"
#include "Log.h"

Control::Control(Joystick *left, Joystick *right,
								 Joystick *gamepad, Mode mode, Robot *robot)
	: isTriggered_(11, false), wasTriggered_(11, false),
		gamepadIsTriggered_(16, false), gamepadWasTriggered_(16, false) {
	this->left_ = left;
	this->right_ = right;
	this->control_ = right;

	this->gamepad_ = gamepad;
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

void Control::setGamepadScale(double scale) {
	gamepadScale_ = scale;
}

double Control::left() {
	return left_->GetY() * leftScale_;
}

double Control::right() {
	return right_->GetY() * rightScale_;
}

double Control::gamepadLeft() {
	return gamepad_->GetY() * gamepadScale_;
}

double Control::gamepadRight() {
	// y axis on second stick
	return gamepad_->GetRawAxis(4);
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

bool Control::gamepadButton(int num) { return gamepad_->GetRawButton(num); }

bool Control::gamepadToggleButton(int num) {
	try {
		bool isPressed = gamepadButton(num);
		if(isPressed && !gamepadWasTriggered_[num])
			gamepadIsTriggered_.at(num) = !gamepadIsTriggered_.at(num);

		gamepadWasTriggered_.at(num) = isPressed;
		return gamepadIsTriggered_.at(num);
	} catch (...) {
		robot_->log->info("Button switching failed");
		return false;
	}
}

