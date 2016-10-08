void initialiseRPMCalculations()
{
	sensorValue[leftEncoder] = 0;
	sensorValue[rightEncoder] = 0;
	leftRPMDifference = 0;
	leftPrevious = 0;
	leftTimerDifference = 0;
	leftTimerPrevious = 0;
	rightRPMDifference = 0;
	rightPrevious = 0;
	rightTimerDifference = 0;
	rightTimerPrevious = 0;
	time1[T1] = 0;
	time1[T2] = 0;
	timerCount = 0;
}



void calculateRPMs()
{
	T2Value = time1[T2];
	timerDifference = T2Value - timerPrevious;

	//Left Calculations
	leftRPMDifference = SensorValue[leftEncoder] - leftPrevious;
	leftRPM = leftRPMDifference/leftTimerDifference;

	//Right Calculations
	rightRPMDifference = SensorValue[rightEncoder] - rightPrevious;
	rightRPM = rightRPMDifference/timerDifference;

	//Setting values for next time
	rightPrevious = SensorValue[rightEncoder];
	leftPrevious = SensorValue[leftEncoder];

	timerPrevious = T2Value;
}


void setSpeeds(float leftPower, float rightPower, float leftDifference, float rightDifference, float armPosition, float intakePower, float bLevel, int toss, int lat)
{
	setLiftSpeed(armPosition);
	setIntakeSpeed(intakePower);

	while(time1[T2] < (timerCount + timerDifference))
	{
		leftDCalc -=  (leftDifference - leftRPM)* autoP/100;
		rightDCalc -=  (rightDifference - rightRPM) * autoP/100;
		setDriveSpeed(leftPower + leftDCalc , rightPower - rightDCalc);
		SensorValue[hanger] = toss;
		SensorValue[tosser] = toss;
		SensorValue[latch] = lat;
	}

	calculateRPMs();

	timerCount += timerDifference;
}
