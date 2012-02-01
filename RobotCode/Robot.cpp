#include "Robot.h"
#include "Control.h"
#include "Drive.h"
#include "ImageTracker.h"
#include "Log.h"

Robot::Robot(Type type) : camera(AxisCamera::GetInstance()) {
	this->type_ = type;	

	camera.WriteMaxFPS(AxisCameraParams::kResolution_320x240);
	compressor = new Compressor(1, 4);
	compressor->Start();
	imageTracker = new ImageTracker(this);
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
		drive->addMotor(Drive::Left, new CANJaguar(2), -1);
		drive->addMotor(Drive::Left, new CANJaguar(3), -1);
		drive->addMotor(Drive::Right, new CANJaguar(6), 1);
		drive->addMotor(Drive::Right, new CANJaguar(7), 1);
		
		
		ultrasonic = new AnalogChannel(5);
		gyroChannel = new AnalogChannel(1);
		gyro = new Gyro(gyroChannel);
		gyro->Reset();
		//robot.touchSensor = new DigitalInput(4);
		//robot.bcd = new BcdSwitch(1, 2);
		//imageTracker = new ImageTracker(this);
		break;
	case BotFinal:
		drive->addMotor(Drive::Left, new CANJaguar(2), -1);
		drive->addMotor(Drive::Left, new CANJaguar(3), -1);
		drive->addMotor(Drive::Right, new CANJaguar(4), 1);
		drive->addMotor(Drive::Right, new CANJaguar(5), 1);
		
		ultrasonic = new AnalogChannel(5);
		gyroChannel = new AnalogChannel(1);
		gyro = new Gyro(gyroChannel);
		//robot.touchSensor = new DigitalInput(4);
		//robot.bcd = new BcdSwitch(1, 2);
		break;
	}
	gyro->Reset();
}

Robot::~Robot() {
}
