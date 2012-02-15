#include "Arm.h"

// TODO tune
static const int downPos = 10;
static const int upPos = 90;

Arm::Arm(int motorPort, int bottomLimitPort, int topLimitPort, 
		 EncoderPorts encoderPorts, Robot *robot) {
	pos_ = Down;
	this->robot_ = robot;
	this->armMotor_ = new CANJaguar(motorPort);
	this->bottomLimit_ = new DigitalInput(bottomLimitPort);
	this->topLimit_ = new DigitalInput(topLimitPort);
	this->encoder_ = new Encoder(encoderPorts.a, encoderPorts.b);

	// TODO tune
	this->armControllerUp_ = new PIDController(1.0, 0.0, 0.0, encoder_, armMotor_);
	this->armControllerDown_ = new PIDController(0.5, 0.0, 0.0, encoder_, armMotor_);
}

/**
 * Sets the arm to either Down or Up
 */
void Arm::setPosition(Position pos) {
	setAngle(pos == Up ? upPos : downPos);
	this->pos_ = pos;
}

Arm::Position Arm::position() {
	return pos_;
}

/**
 * Sets the arm angle manually to the specified angle
 */
void Arm::setAngle(double angle) {
	double current = encoder_->Get();
	PIDController &controller = angle > current ? *armControllerUp_ : *armControllerDown_;
	PIDController &otherController = angle > current ? *armControllerDown_ : *armControllerUp_;
	controller.SetSetpoint(angle);
	if(angle < downPos) angle = downPos;
	if(angle > upPos) angle = upPos;
	
	if(otherController.IsEnabled()) otherController.Disable(); 
	if(!controller.IsEnabled()) controller.Enable();
}

bool Arm::lowHit() {
	return (encoder_->Get() < downPos) || bottomLimit_->Get();
}

bool Arm::highHit() {
	return (encoder_->Get() > upPos) || topLimit_->Get();
}

/**
 * apply power manually, for joystick control
 */
void Arm::setPower(double power) {
	if((highHit() && power > 0) || 
	   (lowHit() && power < 0)) {
		return;
	}
	
	if(armControllerUp_->IsEnabled()) armControllerUp_->Disable();
	if(armControllerDown_->IsEnabled()) armControllerDown_->Disable();
	armMotor_->Set(power);
}
