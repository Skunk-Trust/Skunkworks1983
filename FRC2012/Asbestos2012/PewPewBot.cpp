#include "PewPewBot.h"
#include <iostream>

PewPewBot::PewPewBot()
{
	drive = new C1983Drive();
	shooter = new C1983Shooter();
	collector = new C1983Collector(shooter);
	camera = new C1983GlyphCamera();
#if KINECT
	kinect = new C1983Kinect();
#endif
	lStick = new Joystick(1);
	rStick = new Joystick(2);

	driverStation = DriverStation::GetInstance();
	driverStationLCD = DriverStationLCD::GetInstance();
	myEIO = &driverStation->GetEnhancedIO();

	hasResetItem = false;
	yawAlignState = false;
	stableCount = 0;
	shooter->setEnabled(false);
}

PewPewBot::~PewPewBot()
{
}

void PewPewBot::updateDriverStation()
{
	//Blinken Lights
	FRONT_LINE_LED(drive->getLightSensorFront());
	BACK_LINE_LED(drive->getLightSensorBack());
	RPM_LOCK_LED(shooter->isReady());
	AUTO_RANGE_LED(false);
	AUTO_YAW_LED(false);

	//Drive Station LCD
	driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line1,
			"Shooter RPM: %lf", shooter->getRate() * SHOOTER_MAX_SPEED);
	driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Shot: %s",
			shooter->getShotName());
	driverStationLCD->UpdateLCD();
}

int channel = 0;
void PewPewBot::OperatorControl()
{
	int count = 0;//DEBUG (C1983)
	bool shifterToggle = false;
	shooter->setEnabled(false);
	GetWatchdog().SetEnabled(true);
	GetWatchdog().SetExpiration(0.1);
#if DRIVE_PID
	drive->enablePID();
#endif
	//drive->turnPID->Enable();
	//Cleaning
	collector->clean();
	
	while (IsOperatorControl() && !IsDisabled())
	{
		count++;
		if (count % 50 == 0)
		{
#if DRIVE_PID
			//drive->debugPrint();
			//cout << endl;
#endif
			/*cout<<"LSpeed: "<<drive->getL()<<" RSpeed: "<<drive->getR()
			 <<" Speed/Ideal Max: "<<drive->getL()/MAXSPEEDHIGH
			 << "Shooter Power: "<<-(rStick->GetThrottle() + 1)/2<<endl;*/
			//cout<<"Shooter Rate:" << shooter->getRate()<<endl;
			//shooter->debugPrint();
			collector->debugPrint();
			cout << endl;
		}
		updateDriverStation();

		//Set the compressor
		drive->updateCompressor();

		if (yawAlignState && !KEY_ALIGN_BUTTON)
		{
			drive->turnPID->Disable();
			drive->enablePID();
		}
		if (AUTO_TARGET_BUTTON)
		{
			camYawAlign();
		} else if (KEY_ALIGN_BUTTON)
		{
			lineDepthAlign();
		} else
		{
			//Set the drive base to the stick speeds (Joysticks are backwards yo!)
			if (fabs(rStick->GetY()) >= DEADBAND)
			{
				drive->setSpeedR(-rStick->GetY());
			} else
			{
				drive->setSpeedR(0.0);
			}
			if (fabs(lStick->GetY()) >= DEADBAND)
			{
				drive->setSpeedL(-lStick->GetY());
			} else
			{
				drive->setSpeedL(0.0);
			}
		}

		//check for shifting
		if (!shifterToggle && (shifterToggle = SHIFT_BUTTON))
		{
			drive->shift(!(drive->shiftedHigh));
		} else
		{
			shifterToggle = SHIFT_BUTTON;
		}

		//COLLECTOR
		if (COLLECT_BUTTON)
		{
			collector->setAutomatic(true);
			collector->requestCollect();
		} else if (REVERSE_SWITCH)
		{
			collector->setAutomatic(false);
			collector->requestReverse();
		} else if (FORWARD_SWITCH)
		{
			collector->setAutomatic(false);
			collector->requestCollect();
		} else
		{
			collector->requestStop();
		}
		collector->update();
		//END COLLECTOR

		//SHOOTER	
		//Updates the average. Maybe some other stuff later.
#if SHOOTER_PID
		shooter->update();

		if (SHORT_SHOT_SWITCH)
		{
			shooter->setShot(C1983Shooter::kFreethrow);
		} else
		{
			shooter->setShot(C1983Shooter::kKeytop);
		}

		if (ARM_BUTTON)
		{
			shooter->setEnabled(true);
		} else
		{
			shooter->setEnabled(false);
		}
		/*
		 if(rStick->GetRawButton(5))
		 {
		 shooter->setPower(2775.0/SHOOTER_MAX_SPEED);
		 }else{
		 shooter->setPower((rStick->GetThrottle() - 1)/(-2.0));
		 }
		 */
#else
		shooter->update();
		shooter->setJankyPower((rStick->GetThrottle() - 1)/(-2.0));
#endif
		//Check for shot
		if (SHOOT_BUTTON)
		{
			collector->requestShot();
		}
		//END SHOOTER
		//TIPPER
		if (TIPPER_SWITCH)
		{
			drive->tip(true);
		} else
		{
			drive->tip(false);
		}
		//END TIPPER		
		//check for light
		if (LIGHT_BUTTON)
		{
			drive->setLight(true);
		} else
		{
			drive->setLight(false);
		}

		if (lStick->GetRawButton(10))
		{
			drive->resetGyro();
		}
#if SHOOTER_PID
		/*if (lStick->GetRawButton(2) && count/5 == (float)count/5)
		 {
		 shooter->iDown();
		 }
		 if (lStick->GetRawButton(3) && count/5 == (float)count/5)
		 {
		 shooter->iUp();
		 }
		 if (rStick->GetRawButton(5))
		 {
		 shooter->cleanPID();
		 }*/
#endif

		//Check for PID modification DEBUG
#if DRIVE_PID
		if (lStick->GetRawButton(6) && count/5 == (float)count/5)
		{
			drive->pDown();
		}
		if (lStick->GetRawButton(7) && count/5 == (float)count/5)
		{
			drive->pUp();
		}

		if (lStick->GetRawButton(2) && count/5 == (float)count/5)
		{
			drive->iDown();
		}

		if (lStick->GetRawButton(3) && count/5 == (float)count/5)
		{
			drive->iUp();
		}

		if (lStick->GetRawButton(10) && count/5 == (float)count/5)
		{
			drive->dDown();
		}

		if (lStick->GetRawButton(11) && count/5 == (float)count/5)
		{
			drive->dUp();
		}

		if (lStick->GetRawButton(5))
		{
			drive->resetLeftI();
			drive->resetRightI();
		}
#endif
		GetWatchdog().Feed();
		myfile<<count<<","<<drive->getL()<<"\n";
		Wait(0.02);
	}
}

void PewPewBot::Disabled()
{
	//drive->resetEncoders();
#if SHOOTER_PID
	shooter->setEnabled(false);
	shooter->cleanPID();
	collector->clean();
	GetWatchdog().SetEnabled(false);
#endif
	//close file
#if DRIVE_PID
	drive->cleanPID();
#endif
	//Cleaning
	collector->clean();
	while (IsDisabled())
	{
		Wait(0.02);
	}
}

START_ROBOT_CLASS(PewPewBot)
;
