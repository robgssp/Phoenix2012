#ifndef ARM_H
#define ARM_H
#include "Robot.h"


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
		int encoder1, int encoder2, Robot *robot);
	
	void setPosition(Position pos);
	Position position();
	void setAngle(double angle);
	void setPower(double power);
	void intake();

	bool lowHit();
	bool highHit();

	int encoderValue();
private:
	Position pos_;
};

#endif
