/*
	PID.c
	Author: Jack Barker
	Auckland University Robotics Association
*/

/****************************************************************/
/****************** Generic PID Datastructures ******************/
/****************************************************************/

/**
		Used to return values from a PID execution function
**/
typedef struct {
	float speed;
	float difference;
} PidReturnValue;

/**
		Represents a PID controller
**/
typedef struct {
	float kP;
	float kI;
	float kD;
	float Difference;
	float Integral;
	float Derivative;
	int LoopTime;
} PidController;

/**
		Resets a PID controller
**/
void ResetController(PidController controller){
	controller.Difference = 0;
	controller.Integral = 0;
	controller.Derivative = 0;
}

/*************************************************************************************/
/****************** PID Functions specific for "The Fat Controller" ******************/
/*************************************************************************************/

PidController TurnController;
PidController DistanceController;
PidController ArmController;

/**
		Populates the PidReturnValue struct (parameter) with the calculated values for driving straight
		Distance based off of encoders, straightness based off gyro.
**/
void driveStraightCalculation(int distance, int maxSpeed, PidReturnValue *value){
	int difference = distance - GetAverageEncoderValues();

	if(abs(difference) < 100){
		DistanceController.Integral += difference;
	}

	if(difference == 0 || (DistanceController.Difference > 0 && difference < 0) || (DistanceController.Difference < 0 && difference > 0)){
		DistanceController.Integral = 0;
	}
	if(abs(difference) < 150){
		DistanceController.Derivative = DistanceController.Difference - difference;
		}else{
		DistanceController.Derivative = 0;
	}
	DistanceController.Difference = difference;
	int speed = DistanceController.Difference * DistanceController.kP + DistanceController.Integral * DistanceController.kI + DistanceController.Derivative * DistanceController.kD;
	value->speed = speed;
	value->difference = difference;
}

/**
		Populates the PidReturnValue struct (parameter) with the calculated values for driving straight.
		Heading based off gyro.
**/
void turnToHeadingCalculation(int targetHeading, int maxSpeed, PidReturnValue *value){
	int difference = targetHeading - GetHeading();

	if(abs(difference) < 100){
		TurnController.Integral += difference;
	}

	if(difference == 0 || (TurnController.Difference > 0 && difference < 0) || (TurnController.Difference < 0 && difference > 0)){
		TurnController.Integral = 0;
	}
	if(abs(difference) < 150){
		TurnController.Derivative = TurnController.Difference - difference;
		}else{
		TurnController.Derivative = 0;
	}
	TurnController.Difference = difference;
	int speed = TurnController.Difference * TurnController.kP + TurnController.Integral * TurnController.kI + TurnController.Derivative * TurnController.kD;

	value->speed = speed;
	value->difference = difference;
}

/**
		Executes PID for driving straight
**/
int driveStraight(int distance, int maxSpeed, int startHeading, bool reset, int tolerance = 4){

	int countAtValue = 0;
	time1[T3] = 0;

	if(reset){
		SensorValue[leftEncoder] = 0;
		SensorValue[rightEncoder] = 0;
	}
	ResetController(DistanceController);
	while(countAtValue < 5 && time1[T3] < abs(distance * 2.5)){

		PidReturnValue value;
		driveStraightCalculation(distance, maxSpeed, &value);

		PidReturnValue turnValue;
		turnToHeadingCalculation(startHeading, maxSpeed, &turnValue);

		setDrive(value.speed - turnValue.speed, value.speed + turnValue.speed);
		if(abs(value.difference) < tolerance){
			countAtValue++;
			}else{
			countAtValue = 0;
		}
		wait1Msec(DistanceController.LoopTime);
	}
	setDrive(0,0);
	return 0;
}


/**
		Executes PID for driving straight
**/
int driveStraightForTime(int time, int maxSpeed){
	int countAtValue = 0;
	time1[T2] = 0;

	int startHeading = SensorValue[gyro];

	while(time1[T2] < time){
		PidReturnValue turnValue;
		turnToHeadingCalculation(startHeading, abs(maxSpeed), &turnValue);

		setDrive(maxSpeed - turnValue.speed, maxSpeed + turnValue.speed);
		wait1Msec(DistanceController.LoopTime);
	}

	setDrive(0,0);
	return 0;
}

/**
		Executes PID for turning to a heading
**/
int turnToHeading(int targetHeading, int maxSpeed, int tolerance = 10){
	int countAtValue = 0;
	time1[T3] = 0;
	ResetController(TurnController);
	while(countAtValue < 5 && time1[T3] < 8000){

		PidReturnValue value;
		turnToHeadingCalculation(targetHeading, maxSpeed, &value);
		setDrive(-value.speed, value.speed);
		if(abs(value.difference) < tolerance){
			countAtValue++;
			}else{
			countAtValue = 0;
		}
		wait1Msec(TurnController.LoopTime);
	}
	setDrive(0,0);
	return 0;
}

int turnToHeadingDie(int targetHeading, int maxSpeed, int tolerance = 10){
	turnToHeading(targetHeading, maxSpeed, tolerance);
	if(abs(targetHeading - GetHeading()) > tolerance){
		while(true){
			wait1Msec(1000000);
		}
	}
	return 0;
}



/**
		Initialises the PID controllers
**/
void InitControllers(){
	TurnController.kP = 0.9;
	TurnController.kI = 0.025;
	TurnController.kD = -1.5;
	TurnController.LoopTime = 20;

	DistanceController.kP = 0.48;
	DistanceController.kI = 0.075;
	DistanceController.kD = -2.3;
	DistanceController.LoopTime = 20;

	ArmController.kP = 1;
	ArmController.kI = 0;
	ArmController.kD = -0.8;
	ArmController.LoopTime = 20;

}

void armControlCalculation(int armHeight, PidReturnValue *value){
	int difference = armHeight - getArmValue();

	if(abs(difference) < 100  && abs(ArmController.Integral) < 10000){
		ArmController.Integral += difference;
	}

	if((difference == 0 || (ArmController.Difference > 0 && difference < 0) || (ArmController.Difference < 0 && difference > 0))){
		ArmController.Integral = 0;
	}

	if(abs(difference) < 150 ){
		ArmController.Derivative = ArmController.Difference - difference;
		}else{
		ArmController.Derivative = 0;
	}

	ArmController.Difference = difference;
	int speed = ArmController.Difference * ArmController.kP + ArmController.Integral * ArmController.kI + ArmController.Derivative * ArmController.kD;

	if(abs(difference) < 50)
		speed = 0;
	value->speed = speed;
	value->difference = difference;
}


float armPosition = 0;
task armControl{
	while(true){
		PidReturnValue value;
		armControlCalculation(armPosition, &value);
		setLift(value.speed);
	}
}

int oldArmPosition = armPosition;
task armBasic{

	while(true){
		if(oldArmPosition == armPosition){
			continue;
		}
		stopTask(armControl);
		oldArmPosition = armPosition;
		if(getArmValue() < armPosition){
			while(getArmValue() < armPosition){
				setLift(127);
			}
			setLift(15);
			startTask(armControl);
			continue;
		}

		if(getArmValue() > armPosition){
			while(getArmValue() > armPosition){
				setLift(-127);
			}
			setLift(-15);

			if(armPosition == ARM_DOWN){
				stopTask(armControl);
				setLift(-25);
			}else{
				startTask(armControl);
			}
			oldArmPosition = armPosition;
			continue;
		}

	}
}
