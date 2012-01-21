#ifndef PHOENIXCONFIG_H
#define PHOENIXCONFIG_H
#include "WPILib.h"
#include <vector>

namespace ProtoConfig {
typedef CANJaguar Motor;
std::vector<int> leftMotors();
std::vector<int> rightMotors();
};

namespace Config = ProtoConfig;

#endif
