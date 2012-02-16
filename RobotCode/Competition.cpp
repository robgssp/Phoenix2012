#include "WPILib.h"
#include "Robot.h"
#include "Drive.h"
#include "Control.h"
#include "Autonomous.h"
#include "BcdSwitch.h"
#include "ImageTracker.h"
#include "Log.h"
#include "Balance.h"

class Competition : public IterativeRobot {
	Robot robot;

public:
	Competition() : robot(Robot::BotFinal) {

	}
	
	void AutonomousInit() {
		//int value = robot.bcd->value();
		//if (value == 1)
			//robot.autonomous = new ScoreAutonomous(&robot);
		//if (value == 2)
			robot.autonomous = new ScoreAutonomous(&robot);
		//else 
			//robot.autonomous = new Autonomous();
	}
	
	void AutonomousPeriodic() { 
		robot.autonomous->loop();
		robot.log->print();
	}

	void AutonomousDisabled() {
		delete robot.autonomous;
	}
	
	AnalogChannel *analog3;
	void TeleopInit() {
		analog3 = new AnalogChannel(3);
	}

	void TeleopPeriodic() {
		if (robot.control->isBalancing()) {
			robot.balance->loop();
			return;
		}
		robot.drive->setLeft(robot.control->left());
		robot.drive->setRight(robot.control->right());
		robot.drive->setScale(robot.control->throttle());
		robot.drive->setReversed(robot.control->isReversed());
		/* 
		if (robot.control->bridgeDeviceOnOff())) {
			rampDevice->Value{1};
		}
		if (robot.control->bridgeDeviceUpDown())) {
			rampDevice->Set{0};
		}
		*/
		robot.log->info("Left Current: %f", robot.drive->leftCurrent());
		robot.log->info("Right Current: %f", robot.drive->rightCurrent());
		robot.log->info("Dist: %f", robot.ultrasonic->GetValue());
		robot.log->info("Infra: %d", analog3->GetValue());
		robot.log->print();
		
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
	}
};

START_ROBOT_CLASS(Competition);
