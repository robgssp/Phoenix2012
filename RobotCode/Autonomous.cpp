#include "Autonomous.h"
#include "Drive.h"
#include "Log.h"
#include "Dumper.h"
#include "RampDevice.h"

ScoreAutonomous::ScoreAutonomous(Robot *robot) {
	state = DriveToBasket;
	for(int i = 0; i < 3; ++i) distances[i] = 500;
	lastMotorSpeed = .5;
	timePassed = 0;
	this->robot_ = robot;
	robot_->drive->setReversed(true);
	robot->log->info("SA Constructor");
}

void ScoreAutonomous::loop() {
	if (state == End) {
		if (lastMotorSpeed < 0) {
			lastMotorSpeed = lastMotorSpeed - .001;
			robot_->drive->setLeft(lastMotorSpeed);
			robot_->drive->setRight(lastMotorSpeed);
		}
		else {
			robot_->drive->setLeft(0);
			robot_->drive->setRight(0);	
			/*
			robot_->arm->setPosition(Arm::Up);
			timePassed = timePassed + 1;
				if (timePassed < 800) { //Random number for now
					//robot_->deployMotor->Set(.25);
				}
				else {
					robot_->arm->setPosition(Arm::Down);
				}
			*/
		robot_->log->info("End.");
		return;
		}
	}
	else if (state == DriveToBasket) {
		distances[2] = distances[1];
		distances[1] = distances[0];
		distances[0] = robot_->ultrasonic->GetValue();
		int averageDist = 0;
		for(int i = 0; i < 3; ++i) averageDist += distances[i];
		averageDist /= 3;
		if (averageDist <= 30) 
		{
		robot_->log->info("=>End %d, %d %d %d", averageDist, distances[0], distances[1], distances[2]);
		state = End; return; 
		}
		/*
		int Anglea;
			if (Anglea >= 2) {
				robot_->drive->setLeft(.6);
				robot_->drive->setRight(.5);	
			}
			if (Anglea <= 2) {
				robot_->drive->setLeft(.5);
				robot_->drive->setRight(.6);	
			}
			else {
				robot_->drive->setLeft(.5);
				robot_->drive->setRight(.5);	
			}
		*/
		robot_->drive->setLeft(.41);
		robot_->drive->setRight(.5);
		robot_->log->info("Moving...");
		robot_->log->info("Dist: %d", averageDist);
	}
}

// ---

OtherAutonomous::OtherAutonomous(Robot *robot) {
	this->robot_ = robot;
}

void OtherAutonomous::loop() {
	// run forward
	if (!timer.HasPeriodPassed(1.5)) {
		robot_->drive->setLeft(0.75);
		robot_->drive->setRight(0.75);
		// raise arm
	} else if (!timer.HasPeriodPassed(3.5)) {
		robot_->drive->setLeft(0);
		robot_->drive->setRight(0);
		robot_->arm->setPosition(Arm::Up);
	} else if (!timer.HasPeriodPassed(5)) {
		// dump
		robot_->dumper->setDirection(Dumper::Forward);
	}
}

// ---

BridgeAutonomous::BridgeAutonomous(Robot *robot) {
	robot_ = robot;
	count = 1;
}

void BridgeAutonomous::loop() {
	state = DriveToBridge;
	if (state == DriveToBridge){
	    if (robot_->touchSensor->Get()){ //This won't work because we don't have a touchsensor. We must unremark the thing in Competition.cpp when we get one.
	        state = PushDownBridge;
	    }
	    else{
	        robot_->drive->setLeft(.2); //Set motors to drive forward
	        robot_->drive->setRight(.8);
	    }
	}
	else if (state == PushDownBridge){
        robot_->drive->setLeft(0); //Stop motors
        robot_->drive->setRight(0);
	    count = count + 1;
	    if (count > 799){ //Just a random number for now
	    	robot_->rampDevice->set(0);
	    }
	    else { 
	    	robot_->rampDevice->set(1);
	    }
	}
}
