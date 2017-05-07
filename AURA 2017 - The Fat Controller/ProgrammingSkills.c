

void psPickUpCubeAndStars1(){
	driveStraight(750, 127, 0, false, 20);
	turnToHeading(-750, 127, 40);
	stopTask(armBasic);
	stopTask(armControl);
	setLift(-127);
	driveStraight(-300, 127, -750, true, 40);
	while(SensorValue[bum] != 0){wait1Msec(10);}
	setLift(-25);
	SensorValue[armEnc] = 0;
	clawPosition = CLAW_OPEN_DOWN;
	driveStraight(1300, 127, -750, true, 40);
	clawPosition = CLAW_CLOSED;
	driveStraight(1550, 127, -750, false, 40);
	driveStraight(1500, 127, -750, false, 40);
	startTask(armBasic);
	startTask(armControl);
	armPosition = ARM_DOWN + 800;
	wait1Msec(600);
	turnToHeading(-1900, 127, 30);
	wait1Msec(500);
}



void pickUp3OnBack(){
	turnToHeading(-1900, 127, 20);
	armPosition = ARM_DOWN;
	clawPosition = CLAW_OPEN;
	wait1Msec(2000);
	clawPosition = CLAW_OPEN_DOWN - 300;
	driveStraight(780, 127, -1900, true, 40);
	clawPosition = CLAW_CLOSED;
	wait1Msec(700);
	clawPosition = CLAW_CLOSED + 10;
	setDrive(-127,-127);
	wait1Msec(150);
	setDrive(0,0);
	clawPosition = CLAW_CLOSED;
	wait1Msec(700);
	startTask(armBasic);
	startTask(armControl);
	armPosition = 250;
	driveStraight(-400, 127, -1900, true, 40);
	wait1Msec(500);
	dumpComplete = false;
	startTask(dump);
	while(!dumpComplete){wait1Msec(1);};
	setDrive(0,0);
}


void programmingSkills(){
	SensorValue[gyro] = 0;

	setClaw(-127);
	wait1Msec(300);
	setLift(0);
	wait1Msec(200);

	InitControllers();
	AutonomousInit();
	armPosition = 250;

	clawPosition = CLAW_OPEN;
	wait1Msec(200);
	psPickUpCubeAndStars1();
	waitForDump();
	//knockStarsOffFenceBackwards();
	////
	startTask(clawControl);
	armPosition = ARM_DOWN;
	wait1Msec(400);
	clawPosition = CLAW_CLOSED;
	///
  pickUp3OnBack();
  startTask(armControl);
  startTask(armBasic);
  clawPosition = CLAW_OPEN;
  armPosition = ARM_DOWN;

  turnToHeading(-2450, 127, 20);
  wait1Msec(1000);
  clawPosition = CLAW_OPEN_DOWN;
  driveStraight(1100, 127, -2400, true, 20);
  clawPosition = CLAW_CLOSED;
  wait1Msec(500);
  armPosition = 1300;
  driveStraight(-200, 127, -2300, true, 40);

  turnToHeading(-2000, 127, 40);
  armPosition = 600;
  wait1Msec(600);
  setDrive(-127, -127);
    dumpComplete = false;
  startTask(dump);
  wait1Msec(1500);
	setDrive(0,0);

	armPosition = 800;
	wait1Msec(800);

	turnToHeading(-1900, 127, 40);
	clawPosition = CLAW_OPEN;
	setDrive(127,127);
	wait1Msec(200);
	while(wheelDiff > 5){wait1Msec(50);}
	setDrive(0,0);
	SensorValue[gyro] = 0;
	driveStraight(-450, 127, 0, true, 40);
	armPosition = ARM_DOWN;
	turnToHeading(900, 127, 30);
	smartLower();
	clawPosition = CLAW_OPEN_DOWN;
	setDrive(127,127);
	wait1Msec(3500);
	setDrive(-127,-127);
	wait1Msec(140);
	setDrive(0,0);
	clawPosition = CLAW_CLOSED;
	wait1Msec(1400);
	startTask(armControl);
	startTask(armBasic);
	armPosition = 600;
	driveStraight(-100, 127, 800, true, 40);
	turnToHeading(-90, 127, 20);
	driveStraight(-600, 127, -100, true, 20);
	waitForDump();
	armPosition = 600;
	clawPosition = CLAW_CLOSED;
	wait1Msec(1000);
	turnToHeading(0, 127, 20);
	setDrive(127,127);
	wait1Msec(200);
	while(wheelDiff > 5){wait1Msec(50);}
	setDrive(0,0);
	SensorValue[gyro] = 0;
	driveStraight(-400, 127, 0, true, 20);
	turnToHeading(1000, 127, 20);
	setDrive(127,127);
	wait1Msec(200);
	while(wheelDiff > 5){wait1Msec(50);}
	setDrive(0,0);
	SensorValue[gyro] = 0;
	driveStraight(-400, 127, 0, true, 40);
	turnToHeading(1500, 127, 40);
	setDrive(-127, -127);
	SensorValue[po] = 1;
	wait1Msec(700);
	setDrive(0,0);
	armPosition = 2200;
	wait1Msec(1200);
	SensorValue[po] = 1;
	wait1Msec(500);
	setDrive(127, 127);
	stopTask(armBasic);
	stopTask(armControl);
	setLift(-127);
	wait1Msec(1000);
	setDrive(0,0);
	wait1Msec(10000);
}
