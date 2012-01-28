#include "WPILib.h"
#include "Robot.h"
#include "Drive.h"
#include "Control.h"
#include "Autonomous.h"
#include "BcdSwitch.h"

class PhoenixRobot : public IterativeRobot {
	Robot robot;

public:
	PhoenixRobot() {
		robot.lcd = DriverStationLCD::GetInstance();
		//robot.camera = &AxisCamera::GetInstance();
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
		robot.gyroChannel = new AnalogChannel(1);
		robot.gyro = new Gyro(robot.gyroChannel);
		robot.gyro->Reset();
		//robot.touchSensor = new DigitalInput(4);
		robot.bcd = new BcdSwitch(1, 2);
	}
	
	void AutonomousInit() {
		int value = robot.bcd->value();
		if (value == 1)
			robot.autonomous = new ScoreAutonomous(&robot);
		if (value == 2)
			robot.autonomous = new ScoreAutonomous(&robot);
		else 
			robot.autonomous = new Autonomous();
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
				"Left Current: %f", robot.drive->leftCurrent());
				
		robot.lcd->PrintfLine(DriverStationLCD::kUser_Line2,
				"Right Current: %f", robot.drive->rightCurrent());
		
		robot.lcd->PrintfLine(DriverStationLCD::kUser_Line3,
				"Gyro: %f", robot.gyro->GetAngle());

		float angle = robot.gyro->GetAngle();
		robot.lcd->PrintfLine(DriverStationLCD::kUser_Line3, "%f", angle);
		robot.lcd->UpdateLCD();
	}
};

START_ROBOT_CLASS(PhoenixRobot);
