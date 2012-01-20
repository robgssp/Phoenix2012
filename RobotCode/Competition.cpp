#include "WPILib.h"
#include "Config.h"
#include "Drive.h"
#include "Control.h"
#include "Autonomous.h"

class PhoenixRobot : public IterativeRobot {
	DriverStationLCD *lcd_;
	Drive *drive_;
	Control *control_;
	/*AnalogChannel *ultrasonic_;
	Autonomous *autonomous_;*/

public:
	PhoenixRobot() {
		lcd_ = DriverStationLCD::GetInstance();
		drive_ = new Drive;
		std::vector<int> motorIds = Config::leftMotors();
		for(size_t i = 0; i < motorIds.size(); ++i)
			drive_->addMotor(Drive::Left, new Config::Motor(motorIds[i]), -1);
		
		motorIds = Config::rightMotors();
		for(size_t i = 0; i < motorIds.size(); ++i) 
			drive_->addMotor(Drive::Right, new Config::Motor(motorIds[i]), -1);
		
		control_ = new Control(new Joystick(1), new Joystick(2), Control::Tank);
		control_->setLeftScale(-1);
		control_->setRightScale(-1);
		//ultrasonic_ = new AnalogChannel(5);
	}
	
	void AutonomousInit() {
		//autonomous_ = new BridgeAutonomous;
	}
	
	void AutonomousPeriodic() {
		//autonomous_->loop();
	}

	void TeleopPeriodic() {
		/*drive_->setLeft(control_->left());
		drive_->setRight(control_->right());
		drive_->setScale(control_->throttle());
		drive_->setReversed(control_->isReversed());*/
		lcd_->PrintfLine(DriverStationLCD::kUser_Line1, "ctrl left: %f", control_->left());
		lcd_->PrintfLine(DriverStationLCD::kUser_Line2, "ctrl right: %f", control_->right());
		lcd_->PrintfLine(DriverStationLCD::kUser_Line3, "ctrl throttle: %f", control_->throttle());
		lcd_->PrintfLine(DriverStationLCD::kUser_Line4, "ctrl reversed: %s", control_->isReversed()?"true":"false");
		lcd_->UpdateLCD();
	}
};

START_ROBOT_CLASS(PhoenixRobot);
