#include "Arm.h"
#include "Log.h"

Arm::Arm(int motorPort, int potPort, Robot *robot) {
	pos_ = Down;
	this->robot_ = robot;
	this->armMotor_ = new CANJaguar(motorPort);
	this->encoder_ = new AnalogChannel(potPort);
	startPoint_ = -(encoder_->GetValue());

	// TODO tune
	this->armControllerUp_ = new PIDController(1.0, 0.0, 0.0,
		 this, this);
	this->armControllerDown_ = new PIDController(0.5, 0.0, 0.0,
		 this, this);
}

/**
 * Sets the arm to either Down or Up
 */
void Arm::setPosition(Position pos) {
	switch(pos) {
		case Down:
		case Middle:
		case Up:
			setAngle((int) pos);
			break;
		default:
			if (armControllerUp_->IsEnabled())
				armControllerUp_->Disable();
			if (armControllerDown_->IsEnabled())
				armControllerDown_->Disable();
			break;
	}
	this->pos_ = pos;
}

Arm::Position Arm::position() {
	return pos_;
}

void Arm::setPidFactor(double factor) {
	armControllerUp_->SetPID(factor, 
			armControllerUp_->GetI(),
			armControllerUp_->GetD());
}

double Arm::pidFactor() {
	return armControllerUp_->GetP();
}

/**
 * Sets the arm angle manually to the specified angle
 */
void Arm::setAngle(double angle) {
	/*int current = encoder_->GetValue();
	PIDController &controller = angle > current ? *armControllerUp_ : *armControllerDown_;
	PIDController &other = &controller == armControllerUp_ ? armControllerDown_ : armControllerUp_;
	controller.SetSetpoint(angle);
	if (angle < (int) Down) angle = (int) Down;
	if (angle > (int) Up) angle = (int) Up;

	if (other.IsEnabled()) other.Disable(); 
	if (!controller.IsEnabled()) controller.Enable();*/
	if (!armControllerUp_->IsEnabled()) armControllerUp_->Enable();
	if (armControllerUp_->GetSetpoint() != angle)
		armControllerUp_->SetSetpoint(angle);
	pos_ = None;
}

bool Arm::lowHit() {
	return encoder_->GetValue() < (int) Down;
}

bool Arm::highHit() {
	return encoder_->GetValue() > (int) Up;
}

/**
 * apply power manually, for joystick control
 */
void Arm::setPower(double power) {
	if (power > 0.1 || power < -0.1) {
		if (armControllerDown_->IsEnabled())
			armControllerDown_->Disable();
		if (armControllerUp_->IsEnabled())
			armControllerUp_->Disable();
		armMotor_->Set(power);
	}
}

int Arm::encoderValue() { return -(encoder_->GetValue()) - startPoint_; }

int Arm::startPoint() { return startPoint_; }

double Arm::PIDGet() { return encoderValue(); }

void Arm::PIDWrite(float val) { armMotor_->Set(val); }
