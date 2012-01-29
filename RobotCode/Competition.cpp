#include "WPILib.h"
#include "Robot.h"
#include "Drive.h"
#include "Control.h"
#include "Autonomous.h"
#include "BcdSwitch.h"
#include "ImageTracker.h"
#include "Log.h"

class PhoenixRobot : public IterativeRobot {
	Robot robot;

public:
	PhoenixRobot() {
		robot.lcd = DriverStationLCD::GetInstance();
		robot.camera = &AxisCamera::GetInstance();
		robot.camera->WriteMaxFPS(AxisCameraParams::kResolution_320x240);
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
		//robot.bcd = new BcdSwitch(1, 2);
		robot.imageTracker = new ImageTracker(&robot);
		robot.log = new Log(&robot);
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
	
	void TeleopInit() {
		robot.lcd->PrintfLine(DriverStationLCD::kUser_Line1,
				"Starting teleop...");
		robot.lcd->UpdateLCD();
		//robot.imageTracker->updateImage();
		//robot.imageTracker->writeFiles();
	}

	void TeleopPeriodic() {
		robot.drive->setLeft(robot.control->left());
		robot.drive->setRight(robot.control->right());
		robot.drive->setScale(robot.control->throttle());
		robot.drive->setReversed(robot.control->isReversed());
		robot.log->info("Left Current: %f", robot.drive->leftCurrent());
				
		robot.log->info("Right Current: %f", robot.drive->rightCurrent());
		
		robot.log->info("Gyro: %f", robot.gyro->GetAngle());

		robot.lcd->PrintfLine(DriverStationLCD::kUser_Line3, "%f", robot.gyro->GetAngle());
		
		/*
		// Print out shape matches from camera
		robot.imageTracker->updateImage();
		//robot.imageTracker->writeFiles();
		std::vector<RectangleMatch> matches = robot.imageTracker->matches();
		RectangleMatch topMatch;
		memset(&topMatch, 0, sizeof(topMatch));
		for(size_t i = 0; i < matches.size(); ++i) {
			if(matches[i].score > topMatch.score) topMatch = matches[i];
		}*/
		
		/*robot.log->info("rect %.1f: %.1f, %.1f, %.1f, %.1f", 
				topMatch.score,
				topMatch.corner[1].x,
				topMatch.corner[1].y,
				topMatch.corner[3].x,
				topMatch.corner[3].y);*/
		
		robot.lcd->UpdateLCD();
	}
};

START_ROBOT_CLASS(PhoenixRobot);
