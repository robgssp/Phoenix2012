#ifndef RAMPDEVICE_H_
#define RAMPDEVICE_H_

#include "Victor.h"

class RampDevice {
	SpeedController *control_;
	
	float scale_;
public:
	RampDevice(SpeedController *control, float scale = 1);
	virtual ~RampDevice();
	
	void setScale(float scale);
	void set(float power);
};

#endif
