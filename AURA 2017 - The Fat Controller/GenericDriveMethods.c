void knockStarsOffFenceBackwards(){
	clawPosition = CLAW_CLOSED;
	armPosition = 2300;
	wait1Msec(300);
	clawPosition = 80;
	wait1Msec(1000);
	armPosition = 3800;
	wait1Msec(1000);
	clawPosition = CLAW_CLOSED;
	wait1Msec(900);
	clawPosition = 80;
	wait1Msec(500);
	armPosition = ARM_DOWN;
	wait1Msec(400);
	clawPosition = CLAW_CLOSED;
}

void smartLower(){
	armPosition = ARM_DOWN;
	int heading = SensorValue[gyro];
	while(SensorValue[armPot] > ARM_DOWN + 100){
			clawPosition = CLAW_OPEN;
			setDrive(127,127);
			wait1Msec(500);
			clawPosition = CLAW_OPEN + 100;
			setDrive(-127,-127);
			wait1Msec(500);
			clawPosition = CLAW_OPEN;
	}
	setDrive(0,0);
}

void sweepRight(int lineSpeed){
	armPosition = 1400;
	wait1Msec(600);
	clawPosition = CLAW_OPEN;
	driveToLine(lineSpeed);
	turnToHeading(-1000, 127, 20);
	smartLower();
	clawPosition = CLAW_OPEN_DOWN - 500;
	wait1Msec(600);
	trackLine(2000);
	clawPosition = CLAW_CLOSED - 100;
	wait1Msec(1500);
	armPosition = ARM_DOWN + 400;
	driveStraight(-200, 127, -1000, true, 40);
	turnToHeading(-2000, 127, 30);
	armPosition = 1900;
	waitForDump();
}

void sweepLeft(int lineSpeed){
	armPosition = 1400;
	wait1Msec(600);
	clawPosition = CLAW_OPEN;
	driveToLine(lineSpeed);
	turnToHeading(-2800, 127, 20);
	smartLower();
	clawPosition = CLAW_OPEN_DOWN - 500;
	wait1Msec(600);
	trackLine(2000);
	clawPosition = CLAW_CLOSED - 100;
	wait1Msec(1500);
	driveStraight(-200, 127, -2800, true, 40);
	armPosition = ARM_DOWN + 400;
	turnToHeading(-2000, 127, 30);
	armPosition = 1900;
	waitForDump();
}

bool dumpComplete = false;
task dump(){
	armPosition = 3700;
	dumpComplete = false;
	partDumpComplete = false;
	setDrive(-127, -127);
	wait1Msec(500);
	setDrive(0,0);
	startTask(partDump);
	driveSpeed = -127;
	driveTime = 600;
	startTask(driveForMs);
	while(!partDumpComplete){ wait1Msec(1); }
	dumpComplete = true;
}

bool partDumpComplete = false;
task partDump(){
	while(SensorValue[armPot] < 2200){wait1Msec(10);}
	clawPosition = CLAW_OPEN;
	while(SensorValue[armPot] < 3600){wait1Msec(10);}
	partDumpComplete = true;
}

/**
Drives until the encoders have gone a distance
**/
void driveTill(int distance, int speed){
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;

	while(GetAverageEncoderValues() < distance){
		setDrive(speed, speed);
		wait1Msec(20);
	}
	setDrive(0,0);
}

void waitForDump(){
	dumpComplete = false;
	stopTask(dump);
	startTask(dump);
	while(!dumpComplete){wait1Msec(1);};
}

int lineThreshold = 1000;
bool lineDetected(int tracker){
	if(SensorValue[tracker] < lineThreshold){
		return true;
	}
	return false;
}


int lastSide = -1;
void trackLine(int time){
	bool stillTracking = true;
	time1[t1] = 0;
	while(stillTracking){
		if(time1[t1] > time){
			setDrive(0,0);
			return;
		}
		wait1Msec(40);
		//knows where line is
		if(lineDetected(midLine)){
			setDrive(127,127);
			continue;
		}else if(lineDetected(leftLine)){
			setDrive(80, 127);
			continue;
		}
		else if(lineDetected(rightLine)){
			setDrive(127, 80);
			continue;
		}else if(lineDetected(leftleftLine)){
			setDrive(60, 127);
			continue;
		}
		else if(lineDetected(rightrightLine)){
			setDrive(127, 60);
			continue;
		}

		if(lastSide == 0){
			setDrive(60, 127);
			continue;
		}else
			if(lastSide == 1){
			setDrive(127, 60);
			continue;
		}
		setDrive(0,0);
	}
}

void driveToLine(int speed){
	while(!(lineDetected(leftleftLine) || lineDetected(leftLine) || lineDetected(midLine) || lineDetected(rightLine) || lineDetected(rightRightLine))){
		setDrive(speed, speed);
	}
	setDrive(0,0);
}


task lineTrackerBackground(){
	while(true){
	if(lineDetected(midLine)){
			continue;
		}else if(lineDetected(leftLine)){
			lastSide = 0;
			continue;
		}
		else if(lineDetected(rightLine)){
			lastSide = 1;
			continue;
		}else if(lineDetected(leftleftLine)){
			lastSide = 0;
			continue;
		}
		else if(lineDetected(rightrightLine)){
			lastSide = 1;
			continue;
		}
	}

}
