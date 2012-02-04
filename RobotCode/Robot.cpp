#include "Robot.h"
#include "Control.h"
#include "Drive.h"
#include "ImageTracker.h"
#include "Log.h"

Robot::Robot(Type type) {
	this->type_ = type;	

	//camera = &AxisCamera::GetInstance();
	//camera->WriteMaxFPS(AxisCameraParams::kResolution_320x240);
	//imageTracker = new ImageTracker(this);
	log = new Log(this);
	control = new Control(
			new Joystick(1), new Joystick(2), Control::Tank);
	control->setLeftScale(-1);
	control->setRightScale(-1);
	lcd = DriverStationLCD::GetInstance();
	log = new Log(this);
	drive = new Drive(this);
	
	switch(type) {
	case BotProto:
		compressor->Start();
		drive->addMotor(Drive::Left, 2, -1);
		drive->addMotor(Drive::Left, 3, -1);
		drive->addMotor(Drive::Right, 6, 1);
		drive->addMotor(Drive::Right, 7, 1);
		
		ultrasonic = new AnalogChannel(5);
		gyroChannel = new AnalogChannel(1);
		gyro = new Gyro(gyroChannel);
		gyro->Reset();
		//robot.touchSensor = new DigitalInput(4);
		//robot.bcd = new BcdSwitch(1, 2);
		//imageTracker = new ImageTracker(this);
		break;
	case BotFinal:
		compressor = new Compressor(1, 4);
		drive->addMotor(Drive::Left, 2, -1);
		drive->addMotor(Drive::Left, 3, -1);
		drive->addMotor(Drive::Right, 4, 1);
		drive->addMotor(Drive::Right, 5, 1);
		
		//ultrasonic = new AnalogChannel(2);
		//gyroChannel = new AnalogChannel(1);
		//gyro = new Gyro(gyroChannel);
		//robot.touchSensor = new DigitalInput(4);
		//robot.bcd = new BcdSwitch(1, 2);
		break;
	}
	gyro->Reset();
}

Robot::~Robot() {
}
