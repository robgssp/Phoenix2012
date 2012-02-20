#include "WPILib.h"
#include "Robot.h"
#include "Drive.h"
#include "Control.h"
#include "Autonomous.h"
#include "BcdSwitch.h"
#include "ImageTracker.h"
#include "Log.h"
#include "Balance.h"
#include "Gatherer.h"
#include "Dumper.h"
#include <algorithm>

class Competition : public IterativeRobot {
	Robot robot;

public:
	Competition() : robot(Robot::BotFinal) {
		gathererDirection = Relay::kOff;
	}
	
	void AutonomousInit() {
		int value = robot.bcd->value();
		if (value == 1)
			robot.autonomous = new ScoreAutonomous(&robot);
		else 
			robot.autonomous = new Autonomous();
	}
	
	void AutonomousPeriodic() { 
		robot.autonomous->loop();
		robot.log->print();
	}

	void AutonomousDisabled() {
		delete robot.autonomous;
	}
	
	void TeleopInit() {
		robot.drive->setShiftMode(Drive::Manual);
	}

	Relay::Value gathererDirection;

	void TeleopPeriodic() {
		if (robot.control->button(2)) {
			robot.balance->loop();
			return;
		}

		// drive
		robot.drive->setLeft(robot.control->left());
		robot.drive->setRight(robot.control->right());
		robot.drive->setScale(robot.control->throttle());
		robot.drive->setReversed(robot.control->toggleButton(11));
		robot.drive->setLowShift(robot.control->toggleButton(8));

		// ball gatherer
		if (robot.control->gamepadButton(6)) 
			gathererDirection = Relay::kForward;
		else if (robot.control->gamepadButton(7))
			gathererDirection = Relay::kReverse;
		else if (robot.control->gamepadButton(8))
			gathererDirection = Relay::kOff;
		robot.gatherer->setDirection(gathererDirection);

		// arm
		robot.arm->setPower(robot.control->gamepadLeft());
		if (robot.control->gamepadButton(9))
			robot.arm->setPosition(Arm::Up);
		else
			robot.arm->setPosition(Arm::None);

		if (robot.control->gamepadButton(10))
			robot.arm->setPidFactor(robot.arm->pidFactor() - 0.1);
		if (robot.control->gamepadButton(11))
			robot.arm->setPidFactor(robot.arm->pidFactor() + 0.1);

		// dumper
		/*switch (robot.arm->position()) {
			case Arm::Down:
				robot.dumper->updateIntake();
				break;
			case Arm::Up:
			default:
				robot.dumper->setDeploy(robot.control->gamepadButton(3));
				break;
		}*/
		robot.dumper->setDirection(robot.control->gamepadButton(3) ? 
				Relay::kForward : robot.control->gamepadButton(2) ?
				Relay::kReverse : Relay::kOff);

		// assorted debug
		robot.log->info("Shift %s", robot.control->button(8) ? "low" : "high");
		robot.log->info("ArmPot: %d", robot.arm->encoderValue());
		robot.log->info("pidf: %.1f", robot.arm->pidFactor());
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
