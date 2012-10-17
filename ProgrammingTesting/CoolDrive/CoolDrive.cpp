#include "CoolDrive.h"

CoolDrive::CoolDrive(int frontLeftMotor, int rearLeftMotor,
		int frontRightMotor, int rearRightMotor) {
	this->frontLeftMotor = new Jaguar(frontLeftMotor);
	this->rearLeftMotor = new Jaguar(rearLeftMotor);
	this->frontRightMotor = new Jaguar(frontRightMotor);
	this->rearRightMotor = new Jaguar(rearRightMotor);
}

CoolDrive::~CoolDrive() {
	delete frontLeftMotor;
	delete rearLeftMotor;
	delete frontRightMotor;
	delete rearRightMotor;
}

void CoolDrive::setSpeedLeft(float speed) {
	frontLeftMotor->Set(speed);
	rearLeftMotor->Set(speed);

}

void CoolDrive::setSpeedRight(float speed) {
	frontRightMotor->Set(-speed);
	rearRightMotor->Set(-speed);
}

void CoolDrive::setSpeed(float leftSpeed, float rightSpeed) {
	setSpeedLeft(leftSpeed);
	setSpeedRight(rightSpeed);
}

void CoolDrive::tankDrive(Joystick *leftStick, Joystick *rightStick) {
	setSpeed(leftStick->GetAxis(leftStick->kYAxis), rightStick->GetAxis(rightStick->kYAxis));
}

void CoolDrive::arcadeDrive(Joystick *stick) {
	float y = stick->GetAxis(stick->kYAxis)/2;
	float x = stick->GetAxis(stick->kXAxis)/2;
	setSpeed(y - x, y + x);
}
