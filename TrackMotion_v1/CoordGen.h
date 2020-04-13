// Class to generate the coordinates through t while tracking
// Inputs: current time
// Outputs: nPosition and nVelocity

#pragma once
#include "stdafx.h"
#include <math.h>
//#include <Eigen/Dense> // Include the "Eigen" Matrix lib
#define SPRIAL 1
struct Pose3{
	double x;
	double y;
	double z;
};
struct Volocity3{
	double v_x;
	double v_y;
	double v_z;
};
class CoordGen
{
private:
	/*Middle variables*/
	double r;
	double theta_i;

public:
	
	/*Constructor function*/
	CoordGen(double center_x, double center_y, double center_z, double startpoint_x, double startpoint_y, double startpoint_z);

	/*Parameters*/
	Pose3 center,startPoint;
	double w0;
	double v0;
	double alpha0;
	double a0;
	double tmax;

	/*Inputs*/
	double intervalTime;
	double currentTime;

	/*Outputs*/
	Pose3 nPosition;
	Volocity3 nVelocity;

	/*Methods*/
	void SetPara(double currentTimeInput);
	void PointGen();
	void PointGen(double height);
};
