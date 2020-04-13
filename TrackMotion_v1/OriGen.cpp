#pragma once
#include "stdafx.h"
#include "OriGen.h"

OriGen::OriGen(double inAmplitude,double inAngularSpeed){
	amplitude = inAmplitude;
	angularSpeed = inAngularSpeed;
	xAngle = 0.0;
	yAngle = 0.0;
	zAngle = 0.0;
}

void OriGen::SetTime(double inTime){
	dwPlannedTimeOri = inTime;
}

void OriGen::GetAngle(double angleSpeed){
	//Ramp
	if (dwPlannedTimeOri <= amplitude/angleSpeed){
		xAngle = angleSpeed*dwPlannedTimeOri;
	}
	else //constant speed
	{
		xAngle = amplitude;
	}

	zAngle = angularSpeed*dwPlannedTimeOri;
	yAngle = 0.0;


	/*
	double idleTime;
	idleTime = 3.1415926/4.0/angularSpeed;  //In the first 90 degrees (PI/4), yAngle don't move 
	xAngle = amplitude*sin(angularSpeed*nPlannedTime);
	if (nPlannedTime <= idleTime){
	yAngle = 0.0;
	}else{
	yAngle = -amplitude*sin(angularSpeed*(nPlannedTime-idleTime));
	}
	*/
}