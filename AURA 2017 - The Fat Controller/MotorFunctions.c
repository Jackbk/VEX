/*
	MotorFunctions.c
	Author: Jack Barker
	Auckland University Robotics Association
*/


void setDrive(int leftspeed, int rightspeed){
	motor[leftdrive] = leftspeed;
	motor[leftdrive1] = leftspeed;
	motor[rightdrive] = rightspeed;
	motor[rightdrive1] = rightspeed;
}

void setLift(int speed){
	motor[lift] = speed;
	motor[lift1] = speed;
	motor[lift2] = speed;
	motor[lift3] = speed;
}

void setClaw(int speed){
	motor[claw] = speed;
	motor[claw1] = speed;
}
