#include "Arm.h"
#include "Log.h"
#include <cstdlib>

Arm::Arm(int motorPort, int potPort, Robot *robot) {
	pos_ = Down;
	this->robot_ = robot;
	this->armMotor_ = new CANJaguar(motorPort);
	this->encoder_ = new AnalogChannel(potPort);
	startPoint_ = -(encoder_->GetValue());
	for (int i = 0; i < ARMENCAVGS; ++i)
		encoderValues_[i] = 0;

	// TODO tune
	this->armControllerUp_ = new PIDController(0.12, 0.0, 0.0,
			this, this);
	this->armControllerMiddle_ = new PIDController(0.1, 0.0, 0.0,
			this, this);
	this->armControllerDown_ = new PIDController(0.1, 0.0, 0.0,
			this, this);

	this->armControllerCurrent_ = armControllerDown_;
}

/**
 * Sets the arm to either Down or Up
 */
void Arm::setPosition(Position pos) {
	switch(pos) {
		case Down:
		case Middle:
		case Up:
			setAngle((double) pos);
			break;
		default:
			if (armControllerCurrent_->IsEnabled())
				armControllerCurrent_->Disable();
			break;
	}
	this->pos_ = pos;
}

Arm::Position Arm::position() {
	return pos_;
}

void Arm::setPidFactor(double factor) {
	armControllerCurrent_->SetPID(factor, 
			armControllerCurrent_->GetI(),
			armControllerCurrent_->GetD());
}

bool Arm::isPidEnabled() {
	return armControllerCurrent_->IsEnabled();
}

double Arm::pidFactor() {
	return armControllerCurrent_->GetP();
}

/**
 * Sets the arm angle manually to the specified angle
 */
void Arm::setAngle(double angle) {
	PIDController *armControllerLast_ = armControllerCurrent_;

	/*armControllerCurrent_ = angle > (Up + Middle / 2) ? armControllerUp_ :
		angle < (Down + Middle / 2) ? armControllerDown_ : armControllerMiddle_;*/
	armControllerCurrent_ = armControllerUp_;
	if (armControllerLast_ != armControllerCurrent_) 
		armControllerLast_->Disable();
	armControllerCurrent_->Enable();

	armControllerCurrent_->SetSetpoint(angle);
	pos_ = None;
}

double Arm::targetAngle() { return armControllerCurrent_->GetSetpoint(); }

void Arm::setTargetAngle(double angle) {
	if (angle > 0.1 && angle < -0.1)
		setAngle(targetAngle() + angle);
}

bool Arm::lowHit() {
	return encoderValue() < (int) Down;
}

bool Arm::highHit() {
	return encoderValue() > (int) Up;
}

/**
 * apply power manually, for joystick control
 */
void Arm::setPower(double power) {
	if (armControllerCurrent_->IsEnabled())
		armControllerCurrent_->Disable();
	armMotor_->Set(power);
	robot_->log->info("armvolt: %f", armMotor_->GetOutputCurrent());
}

double Arm::encoderValue() { 
	for (int i = ARMENCAVGS - 1; i > 0; --i) 
		encoderValues_[i] = encoderValues_[i - 1];
	encoderValues_[0] = -(encoder_->GetValue()) - startPoint_; 
	double average = 0;
	for (int i = 0; i < ARMENCAVGS; ++i) { average += encoderValues_[i]; } 
	return average / ARMENCAVGS;
	//return encoder_->GetValue();
}

int Arm::startPoint() { return startPoint_; }

double Arm::PIDGet() { return encoderValue(); }

void Arm::PIDWrite(float val) { armMotor_->Set(val); }
