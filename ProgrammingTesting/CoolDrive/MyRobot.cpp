#include "MyRobot.h"

/**
 * This is a demo program showing the use of the CoolDrive class.
 */

CoolDriveDemo::CoolDriveDemo()
{
	driveBase = new CoolDrive(FRONT_LEFT_MOTOR, REAR_LEFT_MOTOR, FRONT_RIGHT_MOTOR, REAR_RIGHT_MOTOR);
	leftStick = new Joystick(LEFT_JOYSTICK);
	rightStick = new Joystick(RIGHT_JOYSTICK);
}

CoolDriveDemo::~CoolDriveDemo() {
	delete driveBase;
	delete leftStick;
	delete rightStick;
}

void CoolDriveDemo::Autonomous() {
}

void CoolDriveDemo::OperatorControl() {
	while (IsOperatorControl()) {
		driveBase->arcadeDrive(leftStick);
	}
}
