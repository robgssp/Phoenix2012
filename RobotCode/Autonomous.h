#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H
#include "WPILib.h"
#include "Robot.h"
#include "Arm.h"
#include "Control.h"
#include "Dumper.h"
#include "BcdSwitch.h"

/**
 * Autonomous no-op & base class
 */
class Autonomous {
public:
	virtual void loop() {};
	virtual ~Autonomous() {};
};

/**
 * Autonomous to score in the baskets
 */
class ScoreAutonomous : public Autonomous {
	enum States { DriveToBasket, DumpBalls, End };
	States state;
	// storing the past 3 ultrasonic values for averaging
	int distances[3];
	float lastMotorSpeed;
	int timePassed;
	int bcdValue;
	Robot *robot_;
public:
	ScoreAutonomous(Robot *robot);
	void loop();
};

/**
 * Autonomous to lower the bridge
 */
class BridgeAutonomous : public Autonomous {
	enum States { DriveToBridge, PushDownBridge };
	States state;
	Robot *robot_;
	int count;
public:
	BridgeAutonomous(Robot *robot);
	
	void loop();
};

#endif
