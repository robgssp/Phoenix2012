#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H
#include "WPILib.h"

class Autonomous {
public:
	virtual void loop() {};
	virtual ~Autonomous() {};
};

class ScoreAutonomous : public Autonomous {
	enum States { DriveToBasket, DumpBalls };
	States state;
public:
	void loop();
};

class BridgeAutonomous : public Autonomous {
	enum States { DriveToBridge, PushDownBridge };
	States state;
public:
	void loop();
};

#endif
