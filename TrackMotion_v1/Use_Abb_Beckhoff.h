#pragma once
//#include "stdafx.h"
#include "stdio.h"
//#include "buliding_machine.h"
#include "conio.h"
#include "math.h"
#include "windows.h"
#include "winsock.h"
#include <iostream>
#include <string>
#include <tchar.h>
#include "mathmatica.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;

class Use_Abb_Beckhoff
{
private:
	SOCKET sockclientABB;  //用于和ABB通讯的socket
	SOCKET sockclientBeckhoff;  //用于和Beckhoff通讯的socket
public:
	/*Define struct robotarget (RAPID type)*/
	struct robtarget
	{
		double pose[7];
		int confData[4];
		long int extjoint[6]; 
	};
	robtarget abbRobtarget;
	robtarget lastAbbRobtarget;    //recording the last robotarget, convenient for the relative move
	robtarget abbRobtargetList5[5];    //5 continous points for move.


	/*Define calibration data*/
	struct clbdata
	{
		double efData[8];
		double ceramicData[8];
		double psdData[12];
	};
	clbdata clbData;

	int beckhoffData[46];   //Data from Beckhoff. Added 4 CCD datas in 2019.10.13. So now the number is 46

	double abbQuaternion[4];	//定义四元数数组
	double abbEulerAngle[3];	//定义欧拉角
	string gettedData;			//Getted data from the Beckhoff. Added 4 CCD datas in 2019.10.13

	

	//typedef int robtarget[17]; 
	//CONST robtarget p15 := [ [600, 500, 225.3], [1, 0, 0, 0], [1, 1,
	//0, 0], [ 11, 12.3, 9E9, 9E9, 9E9, 9E9] ];
	//A position p15 is defined as follows:
	//• The position of the robot: x = 600, y = 500 and z = 225.3 mm in the object
	//coordinate system.
	//• The orientation of the tool in the same direction as the object coordinate
	//system.
	enum m_action {HOMING, TRAVEL, SUCK, RELEASE};
	enum m_mode {MOVEJ, MOVEL};
	enum m_target {ABB, BECKHOFF};  //为什么这几个枚举不能在private里面？？？？？
	//enum m_data {HORI_PSD, VERTI_PSD, EF_HORI_CCD, EF_VERTI_CCD, CON

	int iniAll();		//Initialize the socket library. Need to be run first.
	int clearAll();		//Clean up the socket. Need to be run in the end.
	int manipulateRobot(int action, int mode, robtarget robtarget);
	int connectServer(int target, string ipAddress, int port);
	string getData();		//Get data from Beckhoff
	int setSpeed(int tcp, int ori, int leax, int reax); //Set speed. tcp: linear speed, ori: rotational speed, leax&reax: external axis speed
	int movelABB(robtarget targetPoint);
	string encodeInstruction(robtarget targetPoint);
	string errorCode; //存放errorcode

	int euler2Quater(double* eulerAngle, double* quaternion);// 欧拉角转四元数

	int parseBeckhoffData(string msgBeckhoff,int* beckhoffData);// 将beckhoff发来的string(int)数据转化为 int
	int beckhoffDataNum;  //number of the data from beckhoff

	/*****************************************/
	//very important function, all the data were transformed to double type with unit mm or rad
	double beckhoffDataDouble[34];	//real data from beckhoff, data in format of double. units: mm or rad.
	//Added 4 datas in 20191013, so now the number is 30+4=34
	/*
	| [0] | [1] | [2] | [3] | [4] | [5] | [6] | [7] | [8] | [9] | [10] | [11] | [12] | [13] | [14] | [15] |
	|CCD1 |CCD2 |CCD3 |CCD4 |CCD5 |CCD6 |CCD7 |CCD8 |CCD13|CCD14|CCD15 |CCD16 |CCD17 |CCD18 |CCD19 |CCD20 |

	| [16] | [17] | [18] | [19] | [20] | [21] | [22] | [23] | [24] | [25] | [26] | [27] |    [28]    |    [29]    |
	| PSD1 | PSD2 | PSD3 | PSD4 | PSD5 | PSD6 | PSD7 | PSD8 | PSD9 | PSD10| PSD11| PSD12|GrandienterX|GrandienterY| 

	| [30] | [31]  | [32]  | [33]  |
	| CCD9 | CCD10 | CCD11 | CCD12 |
	*/
	int dataInt2Double(int* beckhoffData, double* beckhoffDataDouble); 
	/*****************************************/
	
	int beckhoffDataDoubleNum;  //number of the physical datas

	double efCeramicDistance1; //distance between the end effector(CCD) and the ceramic when first catching, in average.

	int suckerAction(int action);

	int getBeckhoffSockData(string msgBeckhoff);

	/***************************/
	double poseCrmcInEf[3];    //pose of the ceramic in Ef
	// Sequence: from the CS of Ef to to the CS of crmc. 
	// Firstly, move the CS of the Ef along its own X and Y axes by [1] and [2], respectively.
	// Then rotate around  its own Z axis by [3] (rad).
	int ceramicInEf(double* beckhoffDataDouble, double* poseCrmcInEf, clbdata clbData);
	/***************************/
	
	int lXing(double x11,double y11,double x12,double y12,double x21,double y21,double x22,double y22,double *retP);
	int lCntrXing(double x11,double y11,double a1,double x12,double y12,double a2,double x21,double y21,double a3,double x22,double y22,double a4, double *cp);
	int moveContPoints(int numPoints); //move along max 5 continous points. These points are saved in abbRobtargetList[5].

	/***************************/
	double EfOfstInRef[3]; //dx,dy,dtheta. Meaning that the RCS(Reference coordinate system) firstly move along its own axes for dx and dy, than rotate around its new axis for dtheta
	int getEfOfstInRef();  //Calculate the dx,dy,dtheta.
	/***************************/

	/***************************/
	double CrmcOfstInRef[3]; 
	//Meaning that the RCS(Reference coordinate system) firstly move along its own axes for dx and dy
	//than rotate around its new axis for dtheta to the RCS
	double refInEf[3];
	//Relative to the poseCrmcInEf[3], meaning that move the WCS(EF) to the CS of the Ref(RCS).
	// Sequence: from the CS of Ef to to the RCS. 
	// Firstly, move the CS of the Ef along its own X and Y axes by [1] and [2], respectively.
	// Then rotate around  its own Z axis by [3] (rad).
	int getCrmcOfstInRef();  //Calculate the dx,dy,dtheta of CrmcOfstInRef[3] from EfOfstInRef[3] and poseCrmcInEf[3];
	/***************************/

	double thetaWCS2Ef; //The angle between the WCS and the CS of Ef, meaning that rotate the WCS around its z axis by thetaWCStoEf, WCS paralleling with Ef CS.

	int correctPose();
};
