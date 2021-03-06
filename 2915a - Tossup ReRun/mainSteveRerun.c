#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    leftDrive1,     sensorNone)
#pragma config(Sensor, dgtl1,  rightFront,     sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  rightBack,      sensorSONAR_cm)
#pragma config(Sensor, dgtl5,  backRight,      sensorSONAR_cm)
#pragma config(Sensor, dgtl7,  backLeft,       sensorSONAR_cm)
#pragma config(Sensor, dgtl9,  leftBack,       sensorSONAR_cm)
#pragma config(Sensor, in2,    pot,            sensorPotentiometer)
#pragma config(Sensor, dgtl1,  tosser,         sensorDigitalOut)
#pragma config(Sensor, dgtl2,  hanger,         sensorDigitalOut)
#pragma config(Sensor, dgtl11, latch,          sensorDigitalOut)
#pragma config(Sensor, dgtl12, bump,           sensorDigitalIn)
#pragma config(Sensor, I2C_1,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           leftLiftTop,   tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           leftLiftBottom, tmotorVex393, openLoop)
#pragma config(Motor,  port3,           leftIntake,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           leftDriveFront, tmotorVex393, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port5,           leftDriveBack, tmotorVex393, openLoop)
#pragma config(Motor,  port6,           rightDriveFront, tmotorVex393, openLoop)
#pragma config(Motor,  port7,           rightDriveBack, tmotorVex393, openLoop, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port8,           rightIntake,   tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           rightLiftBottom, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          rightLiftTop,  tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "definitions.c"
#include "MotorControlFunctions.c"
#include "PIDFunctions.c"
#include "RerunFunctions.c"

void pre_auton()
{


	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	//StopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	initialiseRPMCalculations();
	#include "autoblue/blue_buckyowngoal.c"
	wait1Msec(10000);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

//Driver Control variables
float leftPower, rightPower, intakePower, liftPower;


task usercontrol()
{
	initialiseRPMCalculations();
	sensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
	// User control code here, inside the loop
	time1[T1] = 0;
	bool flipper = false;
	int trimD = 1;
	int tosserValue = 0;
	int latchValue = 0;
	while (true)
	{
		// This is the main execution loop for the user control program. Each time through the loop
		// your program should update motor + servo values based on feedback from the joysticks.

		// .....................................................................................
		// Insert user code here. This is where you use the joys[[pp
		//pvtick values to update your motors, etc.
		//		// .....................................................................................

		leftPower = vexRT[Ch3];
		rightPower = vexRT[Ch2];

		intakePower = vexRT[Btn6U] * 127 - vexRT[Btn6D] * 127;

		if(vexRT[Btn5U] == 1){
			liftPower = (127);
			trimD = 1;
		}
		else if(vexRT[Btn5D] == 1){
			liftPower = (-127);
			trimD = 1;
		}
		else{
			liftPower = (15*trimD);

		}
		setDriveSpeed(leftPower, rightPower);

		setLiftSpeed(liftPower);

		setIntakeSpeed(intakePower);

		if(vexRT[Btn8u] == 1){
			tosserValue = 1;
			SensorValue[hanger] = 1;
			SensorValue[tosser] = 1;
		}
		if(vexRT[Btn8d] == 1){
			tosserValue = 0;
			SensorValue[hanger] = 0;
			SensorValue[tosser] = 0;
		}

		if(vexRT[Btn7u] == 1){
			latchValue = 1;
			SensorValue[latch] = 1;
		}
		if(vexRT[Btn7d] == 1){
			latchValue = 0;
			SensorValue[latch] = 0;
		}

		while(time1[T1] < (timerCount + timerDifference)){}

		timerCount += timerDifference;
		calculateRPMs();
		writeDebugStream("setSpeeds(%d,%d,%f,%f,%d,%d, %f,%f,%f);\r\n", leftPower,rightPower,leftRPM,rightRPM,liftPower,intakePower, nAvgBatteryLevel, tosserValue, latchValue);
	}
}
