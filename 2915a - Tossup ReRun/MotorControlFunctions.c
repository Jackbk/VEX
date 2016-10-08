void setDriveSpeed(float lspeed, float rspeed)
{
	motor[leftDriveBack] = lspeed;
	motor[leftDriveFront] = lspeed;
	motor[rightDriveBack] = rspeed;
	motor[rightDriveFront] = rspeed;
}

void setLiftSpeed(float speed)
{
	motor[leftLiftTop] = speed;
	motor[leftLiftBottom] = speed;
	motor[rightLiftTop] = speed;
	motor[rightLiftBottom] = speed;
}

void setIntakeSpeed(float speed)
{
	motor[rightIntake] = speed;
	motor[leftIntake] = speed;
}
