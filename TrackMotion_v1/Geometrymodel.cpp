#include "Geometrymodel.h"
Geometrymodel::Geometrymodel()
{
	/*Please initialize all the parameters here*/
	// Parameters of PSD1
	psd[0].psdparam.axisName = Z_AXIS;
	psd[0].psdparam.d_1 = 283.7;//dx_yz
	psd[0].psdparam.d_2 = -128.25;//dy_zx
	psd[0].psdparam.theta_1 = 0.0;//theta_z
	psd[0].psdparam.theta_2 = 0.0;//theta_x
	// Parameters of PSD2
	psd[1].psdparam.axisName = Z_AXIS;
	psd[1].psdparam.d_1 = 283.7;//dx_yz
	psd[1].psdparam.d_2 = 128.25;//dy_zx
	psd[1].psdparam.theta_1 = 0.0;//theta_z
	psd[1].psdparam.theta_2 = 0.0;//theta_x
	// Parameters of PSD3
	psd[2].psdparam.axisName = Z_AXIS;
	psd[2].psdparam.d_1 = 128.25;//dx_yz
	psd[2].psdparam.d_2 = 283.7;//dy_zx
	psd[2].psdparam.theta_1 = 0.0;//theta_z
	psd[2].psdparam.theta_2 = 0.0;//theta_x
	// Parameters of PSD4
	psd[3].psdparam.axisName = Z_AXIS;
	psd[3].psdparam.d_1 = -128.25;//dx_yz
	psd[3].psdparam.d_2 = 283.7;//dy_zx
	psd[3].psdparam.theta_1 = 0.0;//theta_z
	psd[3].psdparam.theta_2 = 0.0;//theta_x
	// Parameters of PSD5
	psd[4].psdparam.axisName = Z_AXIS;
	psd[4].psdparam.d_1 = -283.7;//dx_yz
	psd[4].psdparam.d_2 = 128.25;//dy_zx
	psd[4].psdparam.theta_1 = 0.0;//theta_z
	psd[4].psdparam.theta_2 = 0.0;//theta_x
	// Parameters of PSD6
	psd[5].psdparam.axisName = Z_AXIS;
	psd[5].psdparam.d_1 = -283.7;//dx_yz
	psd[5].psdparam.d_2 = -128.25;//dy_zx
	psd[5].psdparam.theta_1 = 0.0;//theta_z
	psd[5].psdparam.theta_2 = 0.0;//theta_x
	// Parameters of PSD7
	psd[6].psdparam.axisName = Z_AXIS;
	psd[6].psdparam.d_1 = -128.25;//dx_yz
	psd[6].psdparam.d_2 = -283.7;//dy_zx
	psd[6].psdparam.theta_1 = 0.0;//theta_z
	psd[6].psdparam.theta_2 = 0.0;//theta_x
	// Parameters of PSD8
	psd[7].psdparam.axisName = Z_AXIS;
	psd[7].psdparam.d_1 = 128.25;//dx_yz
	psd[7].psdparam.d_2 = -283.7;//dy_zx
	psd[7].psdparam.theta_1 = 0.0;//theta_z
	psd[7].psdparam.theta_2 = 0.0;//theta_x
	// Parameters of PSD9
	psd[8].psdparam.axisName = Y_AXIS;
	psd[8].psdparam.d_1 = 279.0;//dx_yz
	psd[8].psdparam.d_2 = -55.0;//dz_xy
	psd[8].psdparam.theta_1 = 0.0;//theta_y
	psd[8].psdparam.theta_2 = 0.0;//theta_z
	// Parameters of PSD10
	psd[9].psdparam.axisName = X_AXIS;
	psd[9].psdparam.d_1 = 279.0;//dy_zx
	psd[9].psdparam.d_2 = -55.0;//dz_xy
	psd[9].psdparam.theta_1 = 0.0;//theta_x
	psd[9].psdparam.theta_2 = 0.0;//theta_y
	// Parameters of PSD11
	psd[10].psdparam.axisName = Y_AXIS;
	psd[10].psdparam.d_1 = -279.0;//dx_yz
	psd[10].psdparam.d_2 = -55.0;//dz_xy
	psd[10].psdparam.theta_1 = 0.0;//theta_y
	psd[10].psdparam.theta_2 = 0.0;//theta_z
	// Parameters of PSD12
	psd[11].psdparam.axisName = X_AXIS;
	psd[11].psdparam.d_1 = -279.0;//dy_zx
	psd[11].psdparam.d_2 = -55.0;//dz_xy
	psd[11].psdparam.theta_1 = 0.0;//theta_x
	psd[11].psdparam.theta_2 = 0.0;//theta_y

	//Set the initial valuve for iteration
	qRinL.dtheta_x = 0.0;
	qRinL.dtheta_y = 0.0;
	qRinL.dtheta_z = 0.0;
	qRinL.d_x = 0.0;
	qRinL.d_y = 0.0;
	qRinL.d_z = 0.0;

	//Set the initial value for the target pose
	qTinL.dtheta_x = 0.0;
	qTinL.dtheta_y = 0.0;
	qTinL.dtheta_z = 0.0;
	qTinL.d_x = 0.0;
	qTinL.d_y = 0.0;
	qTinL.d_z = 0.0;

};
void Geometrymodel::SetDf(int psdNum)
{
	//Temp variables
	double d1 = psd[psdNum].psdparam.d_1;
	double d2 = psd[psdNum].psdparam.d_2;
	double theta1 = psd[psdNum].psdparam.theta_1;
	double theta2 = psd[psdNum].psdparam.theta_2;
	double thetax = qRinL.dtheta_x;
	double thetay = qRinL.dtheta_y;
	double thetaz = qRinL.dtheta_z;
	double psdval = psd[psdNum].value;

	switch (psd[psdNum].psdparam.axisName)
	{
	case X_AXIS:
		// (partial)fx/(partial)d_x
		vJPSD[psdNum](0,0)=1.0;
		// (partial)fx/(partial)d_y
		vJPSD[psdNum](0,1)=0.0;
		// (partial)fx/(partial)d_z
		vJPSD[psdNum](0,2)=0.0;
		// (partial)fx/(partial)dtheta_x
		vJPSD[psdNum](0,3)=0.0;
		// (partial)fx/(partial)dtheta_y
		vJPSD[psdNum](0,4)=-cos(thetaz)*sin(thetay)*psdval+sin(thetay)*sin(thetaz)*(tan(theta1)*cos(theta2)*psdval+d1)+cos(thetay)*(tan(theta1)*sin(theta2)*psdval+d2);
		// (partial)fx/(partial)dtheta_z
		vJPSD[psdNum](0,5)=-cos(thetay)*sin(thetaz)*psdval-cos(thetay)*cos(thetaz)*(tan(theta1)*cos(theta2)*psdval+d1);
		break;

	case Y_AXIS:
		// (partial)fy/(partial)d_x
		vJPSD[psdNum](0,0)=0.0;
		// (partial)fy/(partial)d_y
		vJPSD[psdNum](0,1)=1.0;
		// (partial)fy/(partial)d_z
		vJPSD[psdNum](0,2)=0.0;
		// (partial)fy/(partial)dtheta_x
		vJPSD[psdNum](0,3)=(-sin(thetax)*sin(thetaz)+cos(thetax)*cos(thetaz)*sin(thetay))*(tan(theta1)*sin(theta2)*psdval+d1)+(-sin(thetax)*cos(thetaz)-cos(thetax)*sin(thetay)*sin(thetaz))*psdval-cos(thetax)*cos(thetay)*(tan(theta1)*cos(theta2)*psdval+d2);
		// (partial)fy/(partial)dtheta_y
		vJPSD[psdNum](0,4)=cos(thetay)*cos(thetaz)*sin(thetax)*(tan(theta1)*sin(theta2)*psdval+d1)+(-cos(thetay)*sin(thetax)*sin(thetaz))*psdval+sin(thetax)*sin(thetay)*(tan(theta1)*cos(theta2)*psdval+d2);
		// (partial)fy/(partial)dtheta_z
		vJPSD[psdNum](0,5)=(cos(thetax)*cos(thetaz)-sin(thetax)*sin(thetay)*sin(thetaz))*(tan(theta1)*sin(theta2)*psdval+d1)+(-cos(thetax)*sin(thetaz)-cos(thetaz)*sin(thetax)*sin(thetay))*psdval;
		break;

	case Z_AXIS:
		// (partial)fz/(partial)d_x
		vJPSD[psdNum](0,0)=0.0;
		// (partial)fz/(partial)d_y
		vJPSD[psdNum](0,1)=0.0;
		// (partial)fz/(partial)d_z
		vJPSD[psdNum](0,2)=1.0;
		// (partial)fz/(partial)dtheta_x
		vJPSD[psdNum](0,3)=(cos(thetax)*sin(thetaz)+cos(thetaz)*sin(thetax)*sin(thetay))*(tan(theta1)*cos(theta2)*psdval+d1)+(cos(thetax)*cos(thetaz)-sin(thetax)*sin(thetay)*sin(thetaz))*(tan(theta1)*sin(theta2)*psdval+d2)-cos(thetay)*sin(thetax)*psdval;
		// (partial)fz/(partial)dtheta_y
		vJPSD[psdNum](0,4)=(-cos(thetax)*cos(thetay)*cos(thetaz))*(tan(theta1)*cos(theta2)*psdval+d1)+(cos(thetax)*cos(thetay)*sin(thetaz))*(tan(theta1)*sin(theta2)*psdval+d2)-cos(thetax)*sin(thetay)*psdval;
		// (partial)fz/(partial)dtheta_z
		vJPSD[psdNum](0,5)=(cos(thetaz)*sin(thetax)+cos(thetax)*sin(thetay)*sin(thetaz))*(tan(theta1)*cos(theta2)*psdval+d1)+(-sin(thetax)*sin(thetaz)+cos(thetax)*cos(thetaz)*sin(thetay))*(tan(theta1)*sin(theta2)*psdval+d2);
		break;

	default:
		printf("SetDfx error!");
		break;
	}

}

void Geometrymodel::GetJ()
{
	int m = J.rows();
	int n = J.cols();
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			J(i,j) = vJPSD[i](0,j);  //The ith vector's jth element
		}
	}
}

void Geometrymodel::GetDeviation(int psdNum)
{
	//Temp variables
	double d1 = psd[psdNum].psdparam.d_1;
	double d2 = psd[psdNum].psdparam.d_2;
	double theta1 = psd[psdNum].psdparam.theta_1;
	double theta2 = psd[psdNum].psdparam.theta_2;
	double thetax = qRinL.dtheta_x;
	double thetay = qRinL.dtheta_y;
	double thetaz = qRinL.dtheta_z;
	double psdval = psd[psdNum].value;

	switch (psd[psdNum].psdparam.axisName)
	{
	case X_AXIS:
		Fq(psdNum,0) = cos(thetay)*cos(thetaz)*psdval-cos(thetay)*sin(thetaz)*(tan(theta1)*cos(theta2)*psdval+d1)+sin(thetay)*(tan(theta1)*sin(theta2)*psdval+d2)+qRinL.d_x;
		break;
	case Y_AXIS:
		Fq(psdNum,0) = (cos(thetax)*sin(thetaz)+cos(thetaz)*sin(thetax)*sin(thetay))*(tan(theta1)*sin(theta2)*psdval+d1)+(cos(thetax)*cos(thetaz)-sin(thetax)*sin(thetay)*sin(thetaz))*psdval-cos(thetay)*sin(thetax)*(tan(theta1)*cos(theta2)*psdval+d2)+qRinL.d_y;
		break;
	case Z_AXIS:
		Fq(psdNum,0) = (sin(thetax)*sin(thetaz)-cos(thetax)*cos(thetaz)*sin(thetay))*(tan(theta1)*cos(theta2)*psdval+d1)+(cos(thetaz)*sin(thetax)+cos(thetax)*sin(thetay)*sin(thetaz))*(tan(theta1)*sin(theta2)*psdval+d2)+cos(thetax)*cos(thetay)*psdval+qRinL.d_z;
		break;
	default:
		printf("SetFq error!");
		break;
	}
}

void Geometrymodel::PSDTransform()
{
	psd[9].value = -psd[9].value;
	psd[10].value = -psd[10].value;
}

void Geometrymodel::Iteration(Pose6 initialPose)
{

	/*Temp variables*/
	int psdNum;
	int iterNum = 0;   //Number of the iteration
	double epsilon =0.03;  //convergence of the iteration
	Eigen::Matrix<double,6,1> dq;
	Eigen::Matrix<double,12,1> lastFq;
	for (psdNum=0;psdNum<12;psdNum++)
	{
		lastFq(psdNum,0) = 0.0;
	}
	while (iterNum<=10)
	{

		/********************************************************/
		/*    Get J and Fq according to current pose (qRinL)    */
		/********************************************************/
		for (psdNum=0;psdNum<12;psdNum++)
		{
			SetDf(psdNum); // Derive every row vectors (coresponding to each PSD) for the Jacobian matrix
			GetDeviation(psdNum);  // Derive the deviation of the Eq. F (coresponding to each PSD)	
			//debug
			//printf("Fq(%d,0) = %f\n",psdNum,Fq(psdNum,0));

		}
		GetJ(); //Herited from SetDf, Derive the Jacobian Matrix from Each vJPSD

		/*******************************************/
		/*   The norm of the Fq is small enough?   */
		/*******************************************/
		if ((Fq-lastFq).norm()<epsilon)
		{
			break;
		}
		lastFq = Fq;
		/*******************************************/
		/*         Calculate the new qRinL         */
		/*******************************************/
		//q(n+1) = q(n)-(Jt*J)^-1*Jt*Fq
		dq = ((J.transpose()*J).inverse())*(J.transpose()*Fq);
		qRinL.d_x = qRinL.d_x - dq(0,0);
		qRinL.d_y = qRinL.d_y - dq(1,0);
		qRinL.d_z = qRinL.d_z - dq(2,0);
		qRinL.dtheta_x = qRinL.dtheta_x - dq(3,0);
		qRinL.dtheta_y = qRinL.dtheta_y - dq(4,0);
		qRinL.dtheta_z = qRinL.dtheta_z - dq(5,0);
		iterNum++;
		//printf("At the %dth iterations, current qRinL is : [%f mm, %f mm, %f mm, %f rad, %f rad, %f rad]\n",iterNum,qRinL.d_x,qRinL.d_y,qRinL.d_z,qRinL.dtheta_x,qRinL.dtheta_y,qRinL.dtheta_z);
	};
	if (iterNum > 9){
		printf("not converge!\n");
	}else
	{
		//printf("After %d iterations, final qRinL is : [%f mm, %f mm, %f mm, %f rad, %f rad, %f rad]\n",iterNum,qRinL.d_x,qRinL.d_y,qRinL.d_z,qRinL.dtheta_x,qRinL.dtheta_y,qRinL.dtheta_z);
	}
}

void Geometrymodel::GetQuaternionAndOffset(int TinLAngleType)
{
	//Matrices
	Eigen::Matrix<double,3,3> l_R_r;
	Eigen::Matrix<double,3,3> l_R_t;
	Eigen::Matrix<double,3,3> r_R_t;
	Eigen::Matrix<double,3,1> l_d_r;
	Eigen::Matrix<double,3,1> temp31;

	//Calculate l_R_r through qRinL
	double theta1;
	double theta2;
	double theta3;
	switch (TinLAngleType)
	{
	case 0: //XYZ Order
		//Calculate l_R_r through qRinL
		theta1 = qRinL.dtheta_x;
		theta2 = qRinL.dtheta_y;
		theta3 = qRinL.dtheta_z;

		l_R_r(0,0) = cos(theta2)*cos(theta3);
		l_R_r(0,1) = -cos(theta2)*sin(theta3);
		l_R_r(0,2) = sin(theta2);
		l_R_r(1,0) = cos(theta1)*sin(theta3)+cos(theta3)*sin(theta1)*sin(theta2);
		l_R_r(1,1) = cos(theta1)*cos(theta3)-sin(theta1)*sin(theta2)*sin(theta3);
		l_R_r(1,2) = -cos(theta2)*sin(theta1);
		l_R_r(2,0) = sin(theta1)*sin(theta3)-cos(theta1)*cos(theta3)*sin(theta2);
		l_R_r(2,1) = cos(theta3)*sin(theta1)+cos(theta1)*sin(theta2)*sin(theta3);
		l_R_r(2,2) = cos(theta1)*cos(theta2);

		//Calculate l_R_t through qTinL
		theta1 = qTinL.dtheta_x;
		theta2 = qTinL.dtheta_y;
		theta3 = qTinL.dtheta_z;
		l_R_t(0,0) = cos(theta2)*cos(theta3);
		l_R_t(0,1) = -cos(theta2)*sin(theta3);
		l_R_t(0,2) = sin(theta2);
		l_R_t(1,0) = cos(theta1)*sin(theta3)+cos(theta3)*sin(theta1)*sin(theta2);
		l_R_t(1,1) = cos(theta1)*cos(theta3)-sin(theta1)*sin(theta2)*sin(theta3);
		l_R_t(1,2) = -cos(theta2)*sin(theta1);
		l_R_t(2,0) = sin(theta1)*sin(theta3)-cos(theta1)*cos(theta3)*sin(theta2);
		l_R_t(2,1) = cos(theta3)*sin(theta1)+cos(theta1)*sin(theta2)*sin(theta3);
		l_R_t(2,2) = cos(theta1)*cos(theta2);

		//Calculate l_d_r through qRinL
		l_d_r(0,0) = qRinL.d_x;
		l_d_r(1,0) = qRinL.d_y;
		l_d_r(2,0) = qRinL.d_z;

		/* Start formal calculation */
		// Position
		temp31 = -(l_R_r.transpose()*l_d_r);
		qTinR.d_x = temp31(0,0);
		qTinR.d_y = temp31(1,0);
		qTinR.d_z = temp31(2,0);
		// Orientation
		r_R_t = l_R_r.transpose()*l_R_t;
		qTinR.q1 = sqrt(r_R_t.trace()+1.001)/2.0;
		qTinR.q2 = (r_R_t(2,1)-r_R_t(1,2))/(4*qTinR.q1);
		qTinR.q3 = (r_R_t(0,2)-r_R_t(2,0))/(4*qTinR.q1);
		qTinR.q4 = (r_R_t(1,0)-r_R_t(0,1))/(4*qTinR.q1);
		break;

	case 1: //ZXZ Order

		//Calculate l_R_r through qRinL
		theta1 = qRinL.dtheta_x;
		theta2 = qRinL.dtheta_y;
		theta3 = qRinL.dtheta_z;
		l_R_r(0,0) = cos(theta2)*cos(theta3);
		l_R_r(0,1) = -cos(theta2)*sin(theta3);
		l_R_r(0,2) = sin(theta2);
		l_R_r(1,0) = cos(theta1)*sin(theta3)+cos(theta3)*sin(theta1)*sin(theta2);
		l_R_r(1,1) = cos(theta1)*cos(theta3)-sin(theta1)*sin(theta2)*sin(theta3);
		l_R_r(1,2) = -cos(theta2)*sin(theta1);
		l_R_r(2,0) = sin(theta1)*sin(theta3)-cos(theta1)*cos(theta3)*sin(theta2);
		l_R_r(2,1) = cos(theta3)*sin(theta1)+cos(theta1)*sin(theta2)*sin(theta3);
		l_R_r(2,2) = cos(theta1)*cos(theta2);

		//Calculate l_R_t through qTinL
		theta1 = qTinL.dtheta_z;
		theta2 = qTinL.dtheta_x;
		theta3 = -qTinL.dtheta_z;
		l_R_t(0,0) = cos(theta1)*cos(theta3)-cos(theta2)*sin(theta1)*sin(theta3);
		l_R_t(0,1) = -cos(theta1)*sin(theta3)-cos(theta2)*cos(theta3)*sin(theta1);
		l_R_t(0,2) = sin(theta1)*sin(theta2);
		l_R_t(1,0) = cos(theta3)*sin(theta1)+cos(theta1)*cos(theta2)*sin(theta3);
		l_R_t(1,1) = cos(theta1)*cos(theta2)*cos(theta3)-sin(theta1)*sin(theta3);
		l_R_t(1,2) = -cos(theta1)*sin(theta2);
		l_R_t(2,0) = sin(theta2)*sin(theta3);
		l_R_t(2,1) = cos(theta3)*sin(theta2);
		l_R_t(2,2) = cos(theta2);

		//Calculate l_d_r through qRinL
		l_d_r(0,0) = qRinL.d_x;
		l_d_r(1,0) = qRinL.d_y;
		l_d_r(2,0) = qRinL.d_z;

		/* Start formal calculation */
		// Position something wrong founded in 2020.1.19, fixing... seemed to fixed on 2020.1.20
		temp31 = -(l_R_r.transpose()*l_d_r);
		qTinR.d_x = temp31(0,0);
		qTinR.d_y = temp31(1,0);
		qTinR.d_z = temp31(2,0);
		// Orientation
		r_R_t = l_R_r.transpose()*l_R_t;
		qTinR.q1 = sqrt(r_R_t.trace()+1.001)/2.0;
		qTinR.q2 = (r_R_t(2,1)-r_R_t(1,2))/(4.0*qTinR.q1);
		qTinR.q3 = (r_R_t(0,2)-r_R_t(2,0))/(4.0*qTinR.q1);
		qTinR.q4 = (r_R_t(1,0)-r_R_t(0,1))/(4.0*qTinR.q1);
		break;

	default:
		printf("Angle type wrong!!!");

		//Calculate l_R_r through qRinL
		theta1 = qRinL.dtheta_x;
		theta2 = qRinL.dtheta_y;
		theta3 = qRinL.dtheta_z;
		l_R_r(0,0) = cos(theta2)*cos(theta3);
		l_R_r(0,1) = -cos(theta2)*sin(theta3);
		l_R_r(0,2) = sin(theta2);
		l_R_r(1,0) = cos(theta1)*sin(theta3)+cos(theta3)*sin(theta1)*sin(theta2);
		l_R_r(1,1) = cos(theta1)*cos(theta3)-sin(theta1)*sin(theta2)*sin(theta3);
		l_R_r(1,2) = -cos(theta2)*sin(theta1);
		l_R_r(2,0) = sin(theta1)*sin(theta3)-cos(theta1)*cos(theta3)*sin(theta2);
		l_R_r(2,1) = cos(theta3)*sin(theta1)+cos(theta1)*sin(theta2)*sin(theta3);
		l_R_r(2,2) = cos(theta1)*cos(theta2);

		//Calculate l_R_t through qTinL
		theta1 = qTinL.dtheta_x;
		theta2 = qTinL.dtheta_y;
		theta3 = qTinL.dtheta_z;
		l_R_t(0,0) = cos(theta2)*cos(theta3);
		l_R_t(0,1) = -cos(theta2)*sin(theta3);
		l_R_t(0,2) = sin(theta2);
		l_R_t(1,0) = cos(theta1)*sin(theta3)+cos(theta3)*sin(theta1)*sin(theta2);
		l_R_t(1,1) = cos(theta1)*cos(theta3)-sin(theta1)*sin(theta2)*sin(theta3);
		l_R_t(1,2) = -cos(theta2)*sin(theta1);
		l_R_t(2,0) = sin(theta1)*sin(theta3)-cos(theta1)*cos(theta3)*sin(theta2);
		l_R_t(2,1) = cos(theta3)*sin(theta1)+cos(theta1)*sin(theta2)*sin(theta3);
		l_R_t(2,2) = cos(theta1)*cos(theta2);

		//Calculate l_d_r through qRinL
		l_d_r(0,0) = qRinL.d_x;
		l_d_r(1,0) = qRinL.d_y;
		l_d_r(2,0) = qRinL.d_z;

		/* Start formal calculation */
		// Position
		temp31 = -(l_R_r.transpose()*l_d_r);
		qTinR.d_x = temp31(0,0);
		qTinR.d_y = temp31(1,0);
		qTinR.d_z = temp31(2,0);
		// Orientation
		r_R_t = l_R_r.transpose()*l_R_t;
		qTinR.q1 = sqrt(r_R_t.trace()+1.005)/2.0;
		qTinR.q2 = (r_R_t(2,1)-r_R_t(1,2))/(4*qTinR.q1);
		qTinR.q3 = (r_R_t(0,2)-r_R_t(2,0))/(4*qTinR.q1);
		qTinR.q4 = (r_R_t(1,0)-r_R_t(0,1))/(4*qTinR.q1);
		break;
	}

}