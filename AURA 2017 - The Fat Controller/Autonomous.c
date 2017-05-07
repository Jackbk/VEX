void redLeftBabyRageStart(){

	SensorValue[gyro] = 0;

	setLift(-127);
	setClaw(-127);
	wait1Msec(300);
	setLift(0);
	wait1Msec(200);
	AutonomousInit();
	InitControllers();
	AutonomousInit();
	armPosition = 450;

	clawPosition = 1500;
	driveStraight(1850, 127, 0, true, 60);
	clawPosition = CLAW_CLOSED;
	setDrive(-127, -127);
	wait1Msec(500);
	setDrive(0,0);
	driveToLine(-80);
	driveStraight(200, 127, 0, true, 40);
	clawPosition = CLAW_OPEN;
	turnToHeading(-1100, 127, 20);
	driveStraight(-300, 127, -1000, true, 40);
	currentSection = 1;
	int initDumpSection = 1;
	fromLineSweep(1, initDumpSection);
	currentSection = initDumpSection;
	sweepRight(1, 2);
	sweepLeft(1, 1);
	armPosition = ARM_DOWN + 500;
	wait1Msec(100000);
}

void redRightBabyRageStart(){

	SensorValue[gyro] = 0;

	setLift(-127);
	setClaw(-127);
	wait1Msec(300);
	setLift(0);
	wait1Msec(200);
	AutonomousInit();
	InitControllers();
	AutonomousInit();
	armPosition = 450;

	clawPosition = 1500;
	driveStraight(1820, 127, 0, true, 60);
	clawPosition = CLAW_CLOSED;
	setDrive(-127, -127);
	wait1Msec(500);
	setDrive(0,0);
	driveToLine(-80);
	driveStraight(200, 127, 0, true, 40);
	clawPosition = CLAW_OPEN;
	turnToHeading(900, 127, 50);
	driveStraight(-300, 127, 900, true, 40);
	currentSection = 3;
	int initDumpSection = 2;
	fromLineSweep(1, initDumpSection);
	currentSection = initDumpSection;
	sweepRight(1, 3);
	sweepLeft(1, 2);
	armPosition = ARM_DOWN;
armPosition = ARM_DOWN + 500;
	wait1Msec(100000);
}


void redLeftStart(){

	SensorValue[gyro] = 0;

	setLift(-127);
	setClaw(-127);
	setDrive(127,127);
	wait1Msec(300);
	setLift(0);
	wait1Msec(200);
	setDrive(0,0);
	AutonomousInit();
	InitControllers();
	AutonomousInit();
	armPosition = 450;

	clawPosition = 1500;
	clawPosition = CLAW_OPEN;
	setDrive(0,0);
	driveToLine(80);
	clawPosition = CLAW_OPEN;
	turnToHeading(-1000, 127, 40);
	driveStraight(-300, 127, -1000, true, 40);
	currentSection = 1;
	int initDumpSection = 1;
	fromLineSweep(1, initDumpSection);
	currentSection = initDumpSection;
	sweepRight(1, 2);
	sweepRight(1, 3);
armPosition = ARM_DOWN + 500;
	wait1Msec(100000);
}


void redRightStart(){
	SensorValue[gyro] = 0;

	setLift(-127);
	setClaw(-127);
	setDrive(127,127);
	wait1Msec(300);
	setLift(0);
	wait1Msec(200);
	setDrive(0,0);
	AutonomousInit();
	InitControllers();
	AutonomousInit();
	armPosition = 450;

	clawPosition = 1500;
	clawPosition = CLAW_OPEN;
	setDrive(0,0);
	driveToLine(80);
	clawPosition = CLAW_OPEN;
	turnToHeading(1000, 127, 20);
	driveStraight(-300, 127, 1000, true, 40);
	currentSection = 3;
	goingLeft = true;
	int initDumpSection = 3;
	fromLineSweep(1, initDumpSection);
	currentSection = initDumpSection;
	sweepLeft(1, 2);
	sweepRight(1, 3);
armPosition = ARM_DOWN + 500;
	wait1Msec(100000);
}
