#include "WPILib.h"
#include "Robot.h"
#include "Drive.h"
#include "Control.h"
#include "Autonomous.h"

class PhoenixRobot : public IterativeRobot {
	Robot robot;

public:
	PhoenixRobot() {
		robot.lcd = DriverStationLCD::GetInstance();
		robot.drive = new Drive(&robot);
		std::vector<CANJaguar *> motors = robot.leftMotorIds();
		for(size_t i = 0; i < motors.size(); ++i) {
			robot.drive->addMotor(Drive::Left, motors[i], -1);
		}
		motors = robot.rightMotorIds();
		for(size_t i = 0; i < motors.size(); ++i) {
			robot.drive->addMotor(Drive::Right, motors[i], 1);
		}
		
		robot.control = new Control(
				new Joystick(1), new Joystick(2), Control::Tank);
		
		robot.control->setLeftScale(-1);
		robot.control->setRightScale(-1);
		robot.ultrasonic = new AnalogChannel(5);
		robot.gyroChannel = new AnalogChannel(4);
		robot.gyro = new Gyro(robot.gyroChannel);
		robot.gyro->Reset();
		//robot.touchSensor = new DigitalInput(4);
	}
	
	void AutonomousInit() {
		robot.autonomous = new ScoreAutonomous(&robot);
	}
	
	void AutonomousPeriodic() {
		robot.autonomous->loop();
	}
	
	void AutonomousDisabled() {
		delete robot.autonomous;
	}

	void TeleopPeriodic() {
		robot.drive->setLeft(robot.control->left());
		robot.drive->setRight(robot.control->right());
		robot.drive->setScale(robot.control->throttle());
		robot.drive->setReversed(robot.control->isReversed());
		robot.lcd->PrintfLine(DriverStationLCD::kUser_Line1, 
				"ctrl left: %f", robot.control->left());
		
		robot.lcd->PrintfLine(DriverStationLCD::kUser_Line2, 
				"ctrl right: %f", robot.control->right());
		
		robot.lcd->PrintfLine(DriverStationLCD::kUser_Line3, 
				"ctrl throttle: %f", robot.control->throttle());
		
		robot.lcd->PrintfLine(DriverStationLCD::kUser_Line4, 
				"ctrl reversed: %s", robot.control->isReversed()?"true":"false");
		
		robot.lcd->PrintfLine(DriverStationLCD::kUser_Line5,
				"Ultrasonic: %d", robot.ultrasonic->GetValue());
		
		robot.lcd->PrintfLine(DriverStationLCD::kUser_Line6,
				"Gyro: %f", robot.gyroChannel->GetValue());
		
		robot.lcd->UpdateLCD();
	}
};

START_ROBOT_CLASS(PhoenixRobot);
