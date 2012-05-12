#include "RampDevice.h"

RampDevice::RampDevice(SpeedController *control, float scale)
{
	control_ = control;
	scale_ = scale;
}

RampDevice::~RampDevice()
{
	delete control_;
}

void RampDevice::setScale(float scale)
{
	scale_ = scale;
}

void RampDevice::set(float power)
{
	control_->Set(scale_ * power);
}
