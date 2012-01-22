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

void BridgeAutonomous::loop() {
	
}
