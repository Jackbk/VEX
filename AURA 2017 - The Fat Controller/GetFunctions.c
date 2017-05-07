/*
	GetFunctions.c
	Author: Jack Barker
	Auckland University Robotics Association
*/

/**
		Gets the robots heading
**/
int GetHeading(){
	return SensorValue[gyro];
}

/**
		Gets the average encoder value
**/
int GetAverageEncoderValues(){
	return (SensorValue[leftEncoder] - SensorValue[rightEncoder]) / 2;
}
