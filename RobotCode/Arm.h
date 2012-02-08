#ifndef ARM_H
#define ARM_H
#include "Robot.h"

struct EncoderPorts{ int a, b; };

class Arm {
	Robot *robot_;
	CANJaguar *armMotor_;
	Relay *armRelay_;
	DigitalInput *armSwitch_;
	DigitalInput *bottomLimit_;
	DigitalInput *topLimit_;
	Encoder *encoder_;
	PIDController *armControllerUp_;
	PIDController *armControllerDown_;
public:
	enum Position { Down, Up };
	Arm(int motorPort, int bottomLimitPort, int topLimitPort,
		EncoderPorts encoderPorts, Robot *robot);
	
	
	void setPosition(Position pos);
	Position position();
	void setAngle(double angle);
	void setPower(double power);
	void intake();
	void deploy();
	bool deployOne();
private:
	Position pos_;
};

#endif
