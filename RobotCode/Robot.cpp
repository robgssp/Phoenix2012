#include "Robot.h"
#include "Control.h"
#include "Drive.h"
#include "ImageTracker.h"
#include "Log.h"
#include "Balance.h"
#include "BcdSwitch.h"
#include "Gatherer.h"
#include "Arm.h"
#include "Dumper.h"

Robot::Robot(Type type) {
	this->type = type;	
	
	drive = type == BotFinal ? new Drive(2, this) :
		new Drive(this);

	drive->addMotor(Drive::Left, 2, 1);
	drive->addMotor(Drive::Left, 3, 1);
	drive->addMotor(Drive::Right, 4, -1);
	drive->addMotor(Drive::Right, 5, -1);
	
	//camera = &AxisCamera::GetInstance();
	//camera->WriteMaxFPS(AxisCameraParams::kResolution_320x240);
	//imageTracker = new ImageTracker(this);
	
	log = new Log(this);
	
	control = new Control(
			new Joystick(1), new Joystick(2), new Joystick(3), 
			Control::Tank, this);
	control->setLeftScale(-1);
	control->setRightScale(-1);
	control->setGamepadScale(-1);

	log = new Log(this);
	
	switch(type) {
	case BotProto:	
		ultrasonic = new AnalogChannel(5); 
		
		gyroChannel = new AnalogChannel(1);
		
		gyro = new Gyro(gyroChannel);
		balance = new Balance(this);
		
		compressor = new Compressor(1, 5);
		compressor->Start();
		
		//robot.touchSensor = new DigitalInput(4);
		//robot.bcd = new BcdSwitch(1, 2);
		//imageTracker = new ImageTracker(this);
		break;
	case BotFinal:
		compressor = new Compressor(9, 2);
		compressor->Start();
		bcd = new BcdSwitch(11, 12, 13, 14);
		
		ultrasonic = new AnalogChannel(2);
		gatherer = new Gatherer(1, this);
		arm = new Arm(7, 3, this);
		dumper = new Dumper(6, 3, this);
		//gyroChannel = new AnalogChannel(1);
		//gyro = new Gyro(gyroChannel);
		//robot.touchSensor = new DigitalInput(4);
		//robot.bcd = new BcdSwitch(1, 2);
		//robot.rampDevice = new Solenoid(1);
		break;
	}
}

Robot::~Robot() {
}
