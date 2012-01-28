#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H
#include "WPILib.h"
#include "Robot.h"

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
	// storing the past 3 ultrasonic values for averaging
	int distances[3];
	float lastMotorSpeed;
	States state;
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
