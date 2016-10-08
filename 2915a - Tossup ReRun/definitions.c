/*
Lynfield College Robotics

Constant Definitions.

27/11/2013
*/
int rloopsatvalue, lloopsatvalue;

int highGoalHeight = 1360;
float ltspeed, rtspeed;

//		Acceleration speed change per loop
float speedchangeperloop = 0.03;


//		Driving Straight Constants
float accuracy = 1.3, sp = 0.3, si = 0.001, sd = 0;

float change = 0;
float tchange = 00;

//		Turning Constants

float tp = 0.62, ti = 0.0005, td = 0.01;

float sidep = -1;

//		Variable used, but do not need to be set

int rpreviousdifference, lpreviousdifference, lintegral, rintegral, rderivative, lderivative;

float leftDCalc = 0, rightDCalc = 0;

float autoP = 1;

float timerDifference = 60;

float leftRPM = 0;
float leftPrevious = 0;

float leftTimerDifference = 0;
float leftTimerPrevious = 0;

float leftRPMDifference = 0;
float rightRPMDifference = 0;
float rightRPM = 0;
float rightPrevious = 0;

float timerCount = 0;

float rightTimerDifference = 0;
float rightTimerPrevious = 0;
float T2Value = 0;

float timerPrevious = 0;
