#include "Drive.h"
#include <algorithm>

Drive::Drive(Robot *robot) { 
	this->robot_ = robot;
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
	setMotors((reversed_ ? leftMotors_ : rightMotors_), value);
}

void Drive::setRight(double value) {
	setMotors((reversed_ ? rightMotors_ : leftMotors_), value);
}


void Drive::setMotors(const MotorVector &motors, double value) {
	MotorVector::const_iterator iter;
	for(iter = motors.begin(); iter != motors.end(); ++iter) {
		const MotorProperty &m = *iter;
		m.motor->Set(value * scale_ * m.defaultScale *
				(reversed_ ? -1 : 1));
	}
}

void Drive::setScale(double value) {
	scale_ = (value > 1.0 ? 1.0 : (value < 0.0 ? 0.0 : value));
}

double Drive::leftCurrent() {
	return motorCurrent(reversed_ ? leftMotors_ : rightMotors_);
}

double Drive::rightCurrent() {
	return motorCurrent(reversed_ ? rightMotors_ : leftMotors_);
}

double Drive::motorCurrent(const MotorVector &motors) {
	double total = 0;
	MotorVector::const_iterator iter;
	for(iter = motors.begin(); iter != motors.end(); ++iter) {
		const MotorProperty &m = *iter;
		total += m.motor->GetOutputCurrent();
	}
	return total / motors.size();
}

/**
 * Adds a motor to the drive control vectors
 * @param side Side for the motor
 * @param motor Motor to add
 * @param defaultScale scale for the motor to run at
 */
void Drive::addMotor(Side side, CANJaguar *motor, double defaultScale) {
	MotorProperty m = { motor, defaultScale };
	(side == Left ? leftMotors_ : rightMotors_).push_back(m);
}

void Drive::setReversed(bool reversed) {
	this->reversed_ = reversed;
}
