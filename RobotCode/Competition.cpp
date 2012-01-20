#include "WPILib.h"
#include "Config.h"
#include "Drive.h"
#include "Control.h"
#include "Autonomous.h"

class PhoenixRobot : public IterativeRobot {
	Config config;

public:
	PhoenixRobot() {
		config.lcd = DriverStationLCD::GetInstance();
		config.drive = new Drive(&config);
		std::vector<CANJaguar *> motors = config.leftMotors();
		for(size_t i = 0; i < motors.size(); ++i) {
			config.drive->addMotor(Drive::Left, motors[i], -1);
		}
		motors = config.rightMotors();
		for(size_t i = 0; i < motors.size(); ++i) {
			config.drive->addMotor(Drive::Right, motors[i], -1);
		}
		
		config.control = new Control(
				new Joystick(1), new Joystick(2), Control::Tank);
		
		config.control->setLeftScale(-1);
		config.control->setRightScale(-1);
		config.ultrasonic = new AnalogChannel(5);
		config.driveLight = new Relay(5);
	}
	
	void AutonomousInit() {
		config.autonomous = new BridgeAutonomous;
	}
	
	void AutonomousPeriodic() {
		config.autonomous->loop();
	}

	void TeleopPeriodic() {
		config.drive->setLeft(config.control->left());
		config.drive->setRight(config.control->right());
		config.drive->setScale(config.control->throttle());
		config.drive->setReversed(config.control->isReversed());
		config.lcd->PrintfLine(DriverStationLCD::kUser_Line1, 
				"ctrl left: %f", config.control->left());
		
		config.lcd->PrintfLine(DriverStationLCD::kUser_Line2, 
				"ctrl right: %f", config.control->right());
		
		config.lcd->PrintfLine(DriverStationLCD::kUser_Line3, 
				"ctrl throttle: %f", config.control->throttle());
		
		config.lcd->PrintfLine(DriverStationLCD::kUser_Line4, 
				"ctrl reversed: %s", config.control->isReversed()?"true":"false");
		
		config.lcd->UpdateLCD();
	}
};

START_ROBOT_CLASS(PhoenixRobot);
