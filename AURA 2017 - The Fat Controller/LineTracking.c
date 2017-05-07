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
	time1[T1] = 0;
	while(stillTracking){
		if(time1[T1] > time){
			setDrive(0,0);
			return;
		}
		wait1Msec(40);
		//knows where line is
		if(lineDetected(midLine)){
			setDrive(127,127);
			continue;
		}else if(lineDetected(leftLine)){
			setDrive(100, 127);
			continue;
		}
		else if(lineDetected(rightLine)){
			setDrive(127, 100);
			continue;
		}else if(lineDetected(leftLeftLine)){
			setDrive(60, 127);
			continue;
		}
		else if(lineDetected(rightRightLine)){
			setDrive(127, 60);
			continue;
		}

		if(lastSide == 0){
			setDrive(40, 127);
			continue;
		}else
			if(lastSide == 1){
			setDrive(127, 40);
			continue;
		}
		setDrive(0,0);
	}
}

void driveToLine(int speed){
	time1[t4] = 0;
	while(!(lineDetected(leftLeftLine) || lineDetected(leftLine) || lineDetected(midLine) || lineDetected(rightLine) || lineDetected(rightRightLine))){
		setDrive(speed, speed);
		if(time1[t4] > 5000){
			setDrive(0,0);
			wait1Msec(1000000);
		}
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
		}else if(lineDetected(leftLeftLine)){
			lastSide = 0;
			continue;
		}
		else if(lineDetected(rightRightLine)){
			lastSide = 1;
			continue;
		}
	}
}
