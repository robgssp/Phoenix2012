#include "WPILib.h"
#include "Robot.h"
#include "Drive.h"
#include "Control.h"
#include "Autonomous.h"
#include "BcdSwitch.h"
#include "ImageTracker.h"
#include "Log.h"
#include <algorithm>

class Competition : public IterativeRobot {
	Robot robot;

public:
	Competition() : robot(Robot::BotFinal) {

	}
	
	void AutonomousInit() {
		/*
		int value = robot.bcd->value();
		if (value == 1)
			robot.autonomous = new ScoreAutonomous(&robot);
		if (value == 2)
			robot.autonomous = new ScoreAutonomous(&robot);
		else 
			robot.autonomous = new Autonomous();
		*/
		robot.autonomous = new GyroAutonomousTest(&robot);
	}
	
	void AutonomousPeriodic() { 
		robot.autonomous->loop();
		robot.log->print();
	}

	void AutonomousDisabled() {
		delete robot.autonomous;
	}
	
	void TeleopInit() {
		prevCurrent_ = 0;
		robot.drive->setShiftMode(Drive::Manual);
	}

	double prevCurrent_;

	void TeleopPeriodic() {
		robot.drive->setLeft(robot.control->left());
		robot.drive->setRight(robot.control->right());
		robot.drive->setScale(robot.control->throttle());
		robot.drive->setReversed(robot.control->isReversed());
		robot.drive->setLowShift(robot.control->button(8));
		
		robot.log->info("Left Current: %.1f", robot.drive->leftCurrent());
		robot.log->info("Right Current: %.1f", robot.drive->rightCurrent());
		robot.log->info("Compressor: %s", 
				robot.compressor->GetPressureSwitchValue() ? "true" : "false");
		robot.log->info("Max current: %.1f", prevCurrent_ = 
				max(prevCurrent_, robot.drive->current()));
		
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
