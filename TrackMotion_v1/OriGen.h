// Class to generate the coordinates through t while tracking
// Inputs: current time
// Outputs: nPosition and nVelocity

#pragma once
#include "stdafx.h"
#include <math.h>
//#include <Eigen/Dense> // Include the "Eigen" Matrix lib

class OriGen{
private:
	double dwPlannedTimeOri;  //Planned time sent from the robot , in seconds.
	double angularSpeed; //Angular speed around the Xaxis and Yaxis, in rad/s
	double amplitude;  //Maxinum tilt angle, in rads.
	
public:
	/*Constructor function*/
	OriGen(double inAmplitude,double inAngularSpeed);
	/*outputs*/
	double xAngle;  //in rads
	double yAngle;  //in rads
	double zAngle;  //in rads
	/*methods*/
	void SetTime(double plannedTimefromRob);  //input of the planned time
	void GetAngle(double angleSpeed); //calculate the xAngle and the yAngle

};