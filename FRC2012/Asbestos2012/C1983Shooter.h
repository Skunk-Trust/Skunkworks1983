#ifndef __C1983SHOOTER_H
#define __C1983SHOOTER_H
#include "WPIlib.h"
#include "1983Defines2012.h"

class C1983Shooter
{

private:
	//Does the shooter keep itself up to speed
	bool isRunning = false;
	
	Jaguar *shooterjag1; //Jaguars for the shooting wheels
	Jaguar *shooterjag2;
	Jaguar *shooterjag3;
	Jaguar *shooterjag4;

	//Encoder *encoder1;
	//Encoder *encoder2;
	//Encoder *encoder3;
	//Encoder *encoder4;

public:

	//shooting function
	void shoot();

	//setting the velocity needed
	void setVelocity( float velocity );

	//Checks to see if ball is ready to be shot
	bool isReady();

	//Gets the cordinates of the hoop
	//void getCoordinates();
	//void getCorrections();

	//Get the current wheel speed
	float getVelocity();

	//Get the angle needed to shoot at the hoop.
	float getAngle();
	
	//Set the angle that is needed to shoot.
	float angle( float angle );
	
	//Does the wheel try to get up to speed
	void setIsRunning(bool state);
	
	//IS the wheel trying to stay up to speed
	bool isRunning();
	
	//Call this from main loop to get the motor up to speed
	void run();

};
#endif
