/**
Drives until the encoders have gone a distance
**/
void driveTill(int distance, int speed){
	time1[T3] = 0;
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;

	while(GetAverageEncoderValues() < distance && time1[T3] < abs(distance * 2.5)){
		setDrive(speed, speed);
		wait1Msec(20);
	}
	setDrive(0,0);
}

int driveTime = 0;
int driveSpeed = 0;
task driveForMs(){
	setDrive(driveSpeed, driveSpeed);
	wait1Msec(driveTime);
	setDrive(0,0);
}

int currentSection = 1;


void driveToSection(int targetSection){
	if(goingLeft){
		if(abs(SensorValue[gyro] - 1000) < abs(SensorValue[gyro] - -2800)
			turnToHeading(1000, 127, 20);
		else
			turnToHeading(-2800, 127, 20);
	}else{
		if(abs(SensorValue[gyro] - -1000) < abs(SensorValue[gyro] - 2800)
			turnToHeading(-1000, 127, 20);
		else
			turnToHeading(2800, 127, 20);
	}

  int speed = -127;
	if(goingLeft && targetSection < currentSection || !goingLeft && targetSection > currentSection){
		speed = 127;
	}
		driveStraightForTime(abs(targetSection - currentSection) * sectionSweepTime, speed);
}
