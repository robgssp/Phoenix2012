#ifndef ARM_H
#define ARM_H
#include "Robot.h"


class Arm : public PIDSource, public PIDOutput {
	Robot *robot_;
	CANJaguar *armMotor_;
	Relay *armRelay_;
	AnalogChannel *encoder_;
	PIDController *armControllerUp_;
	PIDController *armControllerDown_;
	double pidFactor_;
	int startPoint_;
public:
	enum Position { None = -1, Down = 5, Middle = 20, Up = 35 };
	Arm(int motorPort, int potPort, Robot *robot);
	
	void setPosition(Position pos);
	Position position();
	void setAngle(double angle);
	void setPower(double power);

	bool lowHit();
	bool highHit();

	double pidFactor();
	void setPidFactor(double factor);
	
	double PIDGet();
	void PIDWrite(float val);

	int encoderValue();
	int startPoint();
private:
	Position pos_;
};

#endif
