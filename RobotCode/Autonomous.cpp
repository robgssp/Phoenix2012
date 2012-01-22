#include "Autonomous.h"
#include "Drive.h"

ScoreAutonomous::ScoreAutonomous(Robot *robot) {
	state = DriveToBasket;
	for(int i = 0; i < 3; ++i) distances[i] = 500;
	this->robot_ = robot;
	robot.drive->setReversed(true);
}

void ScoreAutonomous::loop() {
	if (state == End) {
		robot_->drive->setLeft(0);
		robot_->drive->setRight(0);
		robot_->lcd->PrintfLine(DriverStationLCD::kUser_Line1, "End.");
		robot_->lcd->UpdateLCD();
		return;
	} else if (state == DriveToBasket) {
		distances[2] = distances[1];
		distances[1] = distances[0];
		distances[0] = robot_->ultrasonic->GetValue();
		int averageDist = 0;
		for(int i = 0; i < 3; ++i) averageDist += distances[i];
		averageDist /= 3;
		if (averageDist <= 100) { state = End; return; }
		robot_->drive->setLeft(0.5);
		robot_->drive->setRight(0.5);
		robot_->lcd->PrintfLine(DriverStationLCD::kUser_Line1, "Moving...");
		robot_->lcd->PrintfLine(DriverStationLCD::kUser_Line2, "Dist: ", averageDist);
		robot_->lcd->UpdateLCD();
	}
} 

// ---

BridgeAutonomous::BridgeAutonomous(Robot *robot) {
	robot_ = robot;
	count = 1;
	robot_->drive->setReversed(true);
}

void BridgeAutonomous::loop() {
	state = DriveToBridge;
	if (state == DriveToBridge){
	    if (robot_->touchSensor->Get()){ //This won't work because we don't have a touchsensor. We must unremark the thing in Competition.cpp when we get one.
	        state = PushDownBridge;
	    }
	    else{
	        robot_->drive->setLeft(.5); //Set motors to drive forward
	        robot_->drive->setRight(.5);
	    }
	}
	else if (state == PushDownBridge){
        robot_->drive->setLeft(0); //Stop motors
        robot_->drive->setRight(0);
	    count = count + 1;
	    if (count > 799){ //Just a random number for now
	        //armMotor->Set(0); This is the imaginary motor that controls the arm. It remains imaginary for the present time.
	    }
	    else if (count > 399){ 
	        //armMotor->Set(.5);
	    }
	    else{
	    	//armMotor->Set(-.5);
	    }
	}
}
