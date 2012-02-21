#ifndef ARM_H
#define ARM_H
#include "Robot.h"

const int ARMENCAVGS = 5;

class Arm : public PIDSource, public PIDOutput {
	Robot *robot_;
	CANJaguar *armMotor_;
	AnalogChannel *encoder_;
	PIDController *armControllerUp_;
	PIDController *armControllerMiddle_;
	PIDController *armControllerDown_;
	PIDController *armControllerCurrent_;
	double pidFactor_;
	int startPoint_;
	double encoderValues_[ARMENCAVGS];
	void setAngle(double angle);
public:
	enum Position { None = -1, Down = 5, Middle = 20, Up = 35 };
	Arm(int motorPort, int potPort, Robot *robot);
	
	// preset funcs
	void setPosition(Position pos);
	Position position();
	void setPower(double power);

	// joystick funcs
	void setTargetAngle(double angle);
	double targetAngle();

	bool lowHit();
	bool highHit();

	double pidFactor();
	void setPidFactor(double factor);
	bool isPidEnabled();
	
	double PIDGet();
	void PIDWrite(float val);

	double encoderValue();
	int startPoint();
private:
	Position pos_;
};

#endif
