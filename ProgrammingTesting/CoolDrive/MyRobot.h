#ifndef __MY_ROBOT_H
#define __MY_ROBOT_H
#include "WPILib.h"
#include "Config.h"
#include "CoolDrive.h"

class CoolDriveDemo : public SimpleRobot {
	CoolDrive *driveBase; // robot drive system
	Joystick *leftStick; // only joystick
	Joystick *rightStick;
public:
	CoolDriveDemo();
	~CoolDriveDemo();
	void Autonomous();
	void OperatorControl();
};

START_ROBOT_CLASS(CoolDriveDemo);

#endif
