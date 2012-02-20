#include "Drive.h"
#include "Log.h"
#include <algorithm>

Drive::Drive(int shifterPort, Robot *robot) { 
	this->robot_ = robot;
	this->scale_ = 1;
	this->reversed_ = false;
	shifter_ = new Solenoid(shifterPort);
}

Drive::Drive(Robot *robot) {
	this->robot_ = robot;
	this->scale_ = 1;
	this->reversed_ = false;
	shifter_ = NULL;
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

double Drive::current() {
	return max(leftCurrent(), rightCurrent());
}

// max current to run at
static const double maxcurrent = 100.0;

/**
 * if current gets too high, downshift
 */
void Drive::updateShifter() {
	setLowShift(current() > maxcurrent);
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

void Drive::setShiftMode(ShiftMode mode) { this->mode_ = mode; }

void Drive::setLowShift(bool set) {
	shifter_->Set(set); 
}

/**
 * Adds a motor to the drive control vectors
 * @param side Side for the motor
 * @param motor Motor to add
 * @param defaultScale scale for the motor to run at
 */
void Drive::addMotor(Side side, int port, double defaultScale) {
	MotorProperty m = { new CANJaguar(port), defaultScale };
	(side == Left ? leftMotors_ : rightMotors_).push_back(m);
}

void Drive::setReversed(bool reversed) {
	this->reversed_ = reversed;
}
