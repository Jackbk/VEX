/*
ArmClawControl.c
Author: Jack Barker
Auckland University Robotics Association
*/
float clawKp = 0.3;
int clawPosition = 2400;
task clawControl{
	while(true){
		int difference = clawPosition - SensorValue[pot];
		setClaw(-difference * clawKp);
	}
}
