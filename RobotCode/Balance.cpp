#include "Balance.h"

Balance::Balance(Robot *robot) {
	robot_ = robot;	
}

void Balance::loop() {
	angle = robot_->gyro->GetAngle();
	robot_->log->info("Gyro: %f", angle);
	moveBy = .00000125*powf(angle,4); //Can be troubleshooted
	if (angle > 6) { //6 is troubleshootable
		if (moveBy <= .4 && moveBy >= .2) { 
			robot_->drive->setLeft(moveBy); 
			robot_->drive->setRight(moveBy);
		}
		else if (moveBy < .2) {
			robot_->drive->setLeft(.2); 
			robot_->drive->setRight(.2);	
		}
		else {
			robot_->drive->setLeft(.4); 
			robot_->drive->setRight(.4);	
		}
	}
	else if (angle < -6) {
		if (moveBy <= .4 && moveBy >= .2) { 
			robot_->drive->setLeft(moveBy); 
			robot_->drive->setRight(moveBy);
		}
		else if (moveBy < .2) {
			robot_->drive->setLeft(-.2); 
			robot_->drive->setRight(-.2);	
		}
		else {
			robot_->drive->setLeft(-.4); 
			robot_->drive->setRight(-.4);	
		}
	}
	else {
		robot_->drive->setLeft(0); 
		robot_->drive->setRight(0);	
	}
}
