#include "Drive.h"
#include <algorithm>

Drive::Drive() { 
	scale_ = 1;
}

Drive::Drive(MotorVector left, MotorVector right) {
	this->leftMotors_ = left;
	this->rightMotors_ = right;
	scale_ = 1;
}

Drive::~Drive() {
	MotorVector::iterator iter;
	for(iter = leftMotors_.begin(); iter != leftMotors_.end(); ++iter)
		delete iter->motor;
	for(iter = rightMotors_.begin(); iter != rightMotors_.end(); ++iter)
		delete iter->motor;
}

void Drive::setLeft(double value) {
	MotorVector &motors = (reversed_ ? leftMotors_ : rightMotors_);
	MotorVector::iterator iter;
	for(iter = motors.begin(); iter != motors.end(); ++iter) {
		MotorProperty &m = *iter;
		m.motor->Set(value * scale_ * m.defaultScale);
	}
}

void Drive::setRight(double value) {
	MotorVector &motors = (reversed_ ? rightMotors_ : leftMotors_);
	MotorVector::iterator iter;
	for(iter = motors.begin(); iter != motors.end(); ++iter) {
		MotorProperty &m = *iter;
		m.motor->Set(value * scale_ * m.defaultScale);
	}
}

void Drive::addMotor(Side side, Config::Motor *motor, double defaultScale) {
	MotorProperty m = { motor, defaultScale };
	(side == Left ? leftMotors_ : rightMotors_).push_back(m);
}

void Drive::setScale(double value) {
	scale_ = (value > 1.0 ? 1.0 : (value < 0.0 ? 0.0 : value));
}

void Drive::setReversed(bool reversed) {
	this->reversed_ = reversed;
}
