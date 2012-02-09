#ifndef BALANCE_H
#define BALANCE_H
#include "WPILib.h"
#include "Robot.h"
#include "Drive.h"
#include "Math.h"
#include "Log.h"


class Balance {
	Robot *robot_;
	float angle;
	float moveBy;
public:
	Balance(Robot *robot);
	
	void loop();
};

#endif
