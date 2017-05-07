int wheelDiff = 0;
int clawDiff = 0;
task wheelVelocities(){
	int lastValue = 0;
	int lastClawValue = 0;
	while(true){
			wait1Msec(50);
			wheelDiff = abs(GetAverageEncoderValues() - lastValue);
			lastValue = GetAverageEncoderValues();

			clawDiff = abs(SensorValue[pot] - lastClawValue);
			lastClawValue = SensorValue[pot];
	}
}

bool partDumpComplete = false;
task partDump(){
	startTask(clawControl);
	while(getArmValue() < 1050){wait1Msec(10);}
	clawPosition = CLAW_OPEN;
	while(getArmValue() < 1800){wait1Msec(10);}
	partDumpComplete = true;
}



bool dumpComplete = false;
task dump(){
	startTask(armBasic);
	startTask(armControl);
	armPosition = 3700;
	dumpComplete = false;
	partDumpComplete = false;
	driveStraightForTime(400, -127);
	startTask(partDump);
	driveStraightForTime(500, -127);
	time1[t4] = 0;
	while(!partDumpComplete){
		wait1Msec(1);
		if(time1[t4] > 5000){
			stopTask(partDump);
			setLift(0);
			wait1Msec(10000);
		}}
	dumpComplete = true;
}


void waitForDump(){
	dumpComplete = false;
	stopTask(dump);
	startTask(dump);
	while(!dumpComplete){wait1Msec(1);};
}




void smartLower(){
	clawPosition = CLAW_OPEN;
	int armState = 0;

	int loopTime = 200;
	int armMinTolerance = 30;
stopTask(armControl);
			stopTask(armBasic);
			setLift(-127);
	wait1Msec(loopTime * 2);
	int count = 0;
	while(SensorValue[bum] == 1){
		if(count > 3){
			while(true){ wait1Msec(10); stopTask(armControl); stopTask(armBasic); setLift(0); }
		}
		if(armState == 0){
			//Lowering no problem
			stopTask(armControl);
			stopTask(armBasic);
			setLift(-127);
			clawPosition = CLAW_OPEN;

			if(abs(getMotorVelocity(lift)) < armMinTolerance){
				armState = 1;
			}
		}

		if(armState == 1){
			count ++;
			startTask(armBasic);
			startTask(armControl);
			armPosition =getArmValue() + 300;
			wait1Msec(200);
			driveStraight(-400, 127, SensorValue[gyro], true, 20);
			armPosition =ARM_DOWN;
			wait1Msec(400);
			driveStraight(00, 127, SensorValue[gyro], false, 20);
			wait1Msec(loopTime);
			armState = 0;
		}

		if(SensorValue[bum] == 1){
			wait1Msec(60);
		}
	}
	if(timesSwept == 0){
		SensorValue[armEnc] = 0;
		timesSwept++;
	}
	setLift(-25);
}


void smartClose(){
	clawPosition = CLAW_CLOSED;
	wait1Msec(1500);
	driveStraight(-600, 127, SensorValue[gyro], true, 40);
	clawPosition = CLAW_OPEN;
	wait1Msec(500);

	driveStraight(-100, 127, SensorValue[gyro], false, 40);
	clawPosition = CLAW_CLOSED;
	wait1Msec(1100);
	stopTask(clawControl);
	setClaw(-35);

}


void fromLineSweep(int sections, int dumpSection){
	smartLower();

	startTask(clawControl);
	clawPosition = CLAW_OPEN_DOWN - 350;
	wait1Msec(600);

	trackLine(sections * sectionSweepTime * 1.5);

	if(goingLeft)
		currentSection -= sections;
	else
		currentSection +=sections;

	smartClose();
	driveStraight(200, 127, SensorValue[gyro], true, 40);
	startTask(armBasic);
	startTask(armControl);
	setDrive(-127, -127);
	armPosition = ARM_DOWN + 600;
	wait1Msec(200);
	setDrive(0,0);
	wait1Msec(400);
	driveToSection(dumpSection);
	if(abs(SensorValue[gyro] - -2000) < abs(SensorValue[gyro] - 2000))
		turnToHeadingDie(-2000, 127, 60);
	else
		turnToHeadingDie(2000, 127, 60);
	startTask(armBasic);
	startTask(armControl);
	armPosition = 1900;
	waitForDump();
}


void sweepRight(int sections, int dumpSection){
	startTask(armBasic);
	goingLeft = false;
	startTask(armBasic);
	startTask(armControl);
	armPosition = ARM_DOWN + 300;
	wait1Msec(600);
	startTask(clawControl);
	clawPosition = CLAW_OPEN + 200;
	driveToLine(80);
	driveStraight(-50, 127, SensorValue[gyro], true, 40);
	if(abs(SensorValue[gyro] - -900) < abs(SensorValue[gyro] - 2900))
		turnToHeadingDie(-900, 127, 50);
	else
		turnToHeadingDie(2800, 127, 50);
	fromLineSweep(sections, dumpSection);
	currentSection = dumpSection;
}

void sweepLeft(int sections, int dumpSection){
	startTask(armBasic);
	goingLeft = true;
	startTask(armBasic);
	startTask(armControl);
	armPosition = ARM_DOWN + 300;
	wait1Msec(600);
	startTask(clawControl);
	clawPosition = CLAW_OPEN + 200;
	driveToLine(80);
	driveStraight(-50, 127, SensorValue[gyro], true, 40);
	if(abs(SensorValue[gyro] - -2700) < abs(SensorValue[gyro] - 900))
		turnToHeadingDie(-2700, 127, 50);
	else
		turnToHeadingDie(900, 127, 50);
	fromLineSweep(sections, dumpSection);
	currentSection = dumpSection;
}

task clawControlHelper{
	while(true){
		if(clawPosition == CLAW_CLOSED){
			wait1Msec(500);
			while(clawPosition == CLAW_CLOSED){
				if(clawDiff < 3){
					clawPosition = SensorValue[pot] + 120;
				}
			}
		}
	}
}

void AutonomousInit(){
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
	SensorValue[armEnc] = 0;
	startTask(armBasic);
	startTask(clawControl);
	startTask(clawControlHelper);
	startTask(lineTrackerBackground);
	startTask(wheelVelocities);
	InitControllers();
}
