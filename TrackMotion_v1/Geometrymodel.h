//Class to calculate the 3D geometry model of the design to derive the coordinate to be sent to EGM.
//the ORIENTATION is in euler X-Y-Z Order!!!
#pragma once
#include "stdafx.h"
#include <math.h>
#include <Eigen/Dense> // Include the "Eigen" Matrix lib
#define X_AXIS 1
#define Y_AXIS 2
#define Z_AXIS 3
class Geometrymodel
{
private:


public:


	/*Constructor function*/
	Geometrymodel();

	typedef Eigen::Matrix<double,1,6> Vjpsd;  // define the type of the row vector in Jacobian matrix for one PSD
	//Vjpsd vJPSD1, vJPSD2, vJPSD3, vJPSD4, vJPSD5, vJPSD6, vJPSD7, vJPSD8, vJPSD9, vJPSD10, vJPSD11, vJPSD12;
	Vjpsd vJPSD[12]; //Initialized in Constructor function.
	//Jacobian matrix
	Eigen::Matrix<double,12,6> J;
	//Current pose of the RigidBody in CS of the LASER, the ORIENTATION is in X-Y-Z Order!!!
	struct Pose6
	{
		double d_x;
		double d_y;
		double d_z;
		double dtheta_x;
		double dtheta_y;
		double dtheta_z;
	};
	Pose6 qRinL; //The current pose of the Rigid, expressed in the CS of the Laser
	
	// Deviations of the F equation in each iteration
	Eigen::Matrix<double,12,1> Fq;


	/**********/
	/* INPUTS */
	/**********/
	/* Geometry parameters and the reading of the PSDs in the Design*/
	struct Psdparam//Parameters of PSDs
	{
		int axisName;
		double d_1;
		double d_2;
		double theta_1;
		double theta_2;
	};
	struct Psd
	{
		Psdparam psdparam;
		double value;//Readings of PSDs
	};
	Psd psd[12];
	Pose6 qTinL; //The target pose of the Rigid, expressed in the CS of the Laser

	/***********/
	/* OUTPUTS */
	/***********/
	struct Pose7
	{
		double d_x;
		double d_y;
		double d_z;
		double q1;
		double q2;
		double q3;
		double q4;
	};
	Pose7 qTinR;

	/*Methods*/
	void SetPsdOffset();
	void SetDf(int psdNum); // Get the elements of the row vector in Jacobian
	void GetJ(); //Get the Jacobian matrix by conjucating the vectors in column
	void GetDeviation(int psdNum);  //Get the deviation of the Equation and the 0 according to the current qRinL

	void PSDTransform(); //Since the readings of PSD10 and 11 is negative to that in the model. These two readings need to be transformed

	void Iteration(Pose6 initialPose); //Start newton iteration to calculate qRinL

	//Output
	void GetQuaternionAndOffset(int TinLangleType); //0:XYZ, 1:ZXZ Calculate the Quarternion and the Offset of the Target in the Rigid i.e. qTinR

};