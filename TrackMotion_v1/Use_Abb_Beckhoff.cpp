#include "Use_Abb_Beckhoff.h"
//#include "stdafx.h"
using namespace std;
// General Functions



// Functions in class Use_Abb_Beckhoff
int Use_Abb_Beckhoff::iniAll()
{
	//Since WSAStartup() has been runned by EGM class, There is no need to start it again.
	/*
	//Socket Initialization
	WSADATA wsa = {0};
	WSAStartup(MAKEWORD(2,2),&wsa);
	*/

	//ext axis set to 9e9
	for (int i=0; i<6; i++)
	{
		abbRobtarget.extjoint[i]=9e9;
	}

	/*initialize the calibration data. Plese refer to the note book*/
	//new calculated calibration data after fixing the calibration function(16383)
	//new calibration data measured at 20191111
	// Calibration data of the CCDs mounted on the End Effector. Unit: mm. CCD 5~12
	clbData.efData[0] = 207.5151;	//CCD5
	clbData.efData[1] = 207.6225;	//CCD6
	clbData.efData[2] = 208.4820;  //CCD7
	clbData.efData[3] = 208.1304;  //CCD8
	clbData.efData[4] = 208.1304;  //CCD9
	clbData.efData[5] = 207.6909;  //CCD10
	clbData.efData[6] = 206.3627;  //CCD11
	clbData.efData[7] = 208.1304;  //CCD12
	// Calibration data of the CCDs mounted on the Frame to measure the pose of the ceramic. Unit: mm. CCD 13~20
	clbData.ceramicData[0] = 100.2072;   //CCD13
	clbData.ceramicData[1] = 100.4380;   //CCD14
	clbData.ceramicData[2] = 98.9681;   //CCD15
	clbData.ceramicData[3] = 100.0705;   //CCD16
	clbData.ceramicData[4] = 100.5234;   //CCD17
	clbData.ceramicData[5] = 100.0833;   //CCD18
	clbData.ceramicData[6] = 99.9551;   //CCD19
	clbData.ceramicData[7] = 100.5149;   //CCD20
	// Calibration data of the PSDs mounted on the Ef. Unit: mm. PSD 1~12
	clbData.psdData[0] = 1.214;  //PSD1
	clbData.psdData[1] = 0.742;  //PSD2
	clbData.psdData[2] = 0.303;  //PSD3
	clbData.psdData[3] = -0.607;  //PSD4
	clbData.psdData[4] = -0.065;  //PSD5
	clbData.psdData[5] = -0.491;  //PSD6
	clbData.psdData[6] = -0.093;  //PSD7
	clbData.psdData[7] = 0.501;  //PSD8
	clbData.psdData[8] = -0.175;  //PSD9
	clbData.psdData[9] = 0.042;  //PSD10
	clbData.psdData[10] = -0.288;  //PSD11
	clbData.psdData[11] = -0.905;  //PSD12


	/*Initialize the pose data between WCS and EF*/
	thetaWCS2Ef = 0.0;
	return 0;
};
int Use_Abb_Beckhoff::clearAll()
{
	closesocket(sockclientABB);
	closesocket(sockclientBeckhoff);
	//�����׽�����Դ
	WSACleanup();
	return 0;
};

int Use_Abb_Beckhoff::manipulateRobot(int action, int mode, robtarget targetPoint)
{
	/*constructing*/
	switch (action)
	{
	case HOMING:
		movelABB(targetPoint);
		return 0;
		break;
	case TRAVEL:
		movelABB(targetPoint);
		return 0;
		break;
	default:
		return 0;
		break;
	}
};



int Use_Abb_Beckhoff::connectServer(int target, string ipAddress, int port) //����socket�Լ�connect,targetΪABB����Beckhoff
{
	/*����һϵ�б���*/
	int retVal; //return value for connect()
	//���ӷ��������������������׽��ֵ�ַ
	struct sockaddr_in addr = {0};
	//����ABB��е�� �˿���port

	switch (target)
	{
	case ABB:  
		//����socket
		sockclientABB = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); //AF_INET����IPV4
		if(INVALID_SOCKET == sockclientABB)
		{ 
			return 1;
		}
		//���ӷ��������������������׽��ֵ�ַ
		//addr = {0};
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		//����inet_addr()���������ǰѡ�xxx.xxx.xxx.xxx����ʽ��ʾ��IPV4��ַ��ת��ΪIN_ADDR�ṹ���ܹ�
		//���յ���ʽ��unsigned long�ͣ���ΪIN_ADDR�ṹ���еĸ�����յ�S_addr��Ա������������unsigned long�ͣ�
		addr.sin_addr.S_un.S_addr = inet_addr(ipAddress.c_str());//����ip��"127.0.0.1"

		//������������������󣬵�Ȼ����Ҳ����ͨ��connet�����ķ���ֵ�жϵ����������ӳɹ���
		retVal = connect(sockclientABB,(struct sockaddr*)&addr,sizeof(addr));
		if(SOCKET_ERROR == retVal)
		{
			printf("ABB����������ʧ�ܣ�");
			int errornum=WSAGetLastError();
			printf("%d",errornum);
			closesocket(sockclientABB);
			return 1;
		}
		printf("ABB���������ӳɹ���\n");
		return 0;
		break;

		//����Beckhoff �˿���port
	case BECKHOFF:
		/*Define a loop, max ten times. If connect failed, wait 0.5s, connect again.*/
		int i=1;  //loop time;
		while (i < 10)
		{
			//����socket
			sockclientBeckhoff = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); //AF_INET����IPV4
			if(INVALID_SOCKET == sockclientBeckhoff)
			{ 
				return 1;
			}
			//addr = {0};
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			//����inet_addr()���������ǰѡ�xxx.xxx.xxx.xxx����ʽ��ʾ��IPV4��ַ��ת��ΪIN_ADDR�ṹ���ܹ�
			//���յ���ʽ��unsigned long�ͣ���ΪIN_ADDR�ṹ���еĸ�����յ�S_addr��Ա������������unsigned long�ͣ�
			addr.sin_addr.S_un.S_addr = inet_addr(ipAddress.c_str());//����ip��"127.0.0.1"

			//������������������󣬵�Ȼ����Ҳ����ͨ��connet�����ķ���ֵ�жϵ����������ӳɹ���
			retVal = connect(sockclientBeckhoff,(struct sockaddr*)&addr,sizeof(addr));
			if(SOCKET_ERROR == retVal)
			{
				printf("Beckhoff����������ʧ�ܣ�\n");
				int errornum=WSAGetLastError();
				printf("Error number = %d\n �����ٴ�����\n",errornum);
				closesocket(sockclientBeckhoff);
				// return 1;

				Sleep(500);// �ȴ�0.5s
			}
			else
			{
				printf("Beckhoff�������� %d �����ӳɹ���\n", i);
				break;
			}

			i=i+1;
		};


		return 0;
		break;

		/*default:
		printf("����������\n");
		break;*/
	}
	return 0;
}

string Use_Abb_Beckhoff::getData() //��Beckhoff��ȡ����
{
	char instructionSend[80] = "GetData";
	//CHAR szSend[100] = "1 900 0 1300 0.424 -0.451 0.760 -0.195 #";   //�ͻ���  �ȷ�����
	int numsend=send(sockclientBeckhoff,instructionSend,sizeof(instructionSend),0);  //���ͺ���������ͨ������ֵ�жϷ��ͳɹ����
	if (numsend == 0)
	{
		WSAGetLastError();
		errorCode= "Receive From Beckhoff Error!\n";
		return "1";
	}

	//���շ������ش�������
	char szRecv[255] = {0};
	recv(sockclientBeckhoff,szRecv,255,0); //���պ���
	//debug
	//printf("%s\n",szRecv);  //��ʾ���ַ����ĸ�ʽ����������˷��͵����ݡ�
	return szRecv;
}

int Use_Abb_Beckhoff::setSpeed(int tcp, int ori, int leax, int reax) //set the speed of ABB
{
	if (tcp > 150 | ori >70 | leax >150 | reax > 70)
	{
		printf("Current speed is %d mm/s and %d deg/s, too high!",tcp, ori);
		tcp = 10;
		ori = 10;
		leax = 10;
		reax = 10;
	}
	//Maxium 80 Characters can be send one time
	std::string tcpstr = std::to_string(tcp);
	std::string oristr = std::to_string(ori);
	std::string leaxstr = std::to_string(leax);
	std::string reaxstr = std::to_string(reax);
	string temp = "8";  //һ��ʼ�ȷ�8�� ��ʾsetspeed
	temp = temp + ' ' + tcpstr + ' ' + oristr + ' ' + leaxstr + ' ' + reaxstr + ' ' + '#';
	char instructionSend[80];
	strcpy_s(instructionSend, temp.c_str());  // Ҳ���Դ�temp
	//CHAR szSend[100] = "1 900 0 1300 0.424 -0.451 0.760 -0.195 #";   //�ͻ���  �ȷ�����
	int numsend=send(sockclientABB,instructionSend,sizeof(instructionSend),0);  //���ͺ���������ͨ������ֵ�жϷ��ͳɹ����
	if (numsend == 0)
	{
		WSAGetLastError();
		return 1;
		errorCode="Send speed to ABB error\n";
	}
	printf("Speed is set to:");
	printf(temp.c_str());
	//���շ������ش�������,��ʾ�ɹ�setSpeed
	char szRecv[100] = {0};
	int numrecv=recv(sockclientABB,szRecv,100,0); //���պ���
	if (numrecv <= 0)
	{
		return 1;
		errorCode="Receive from ABB error\n";
	};
	printf("%s\n",szRecv);  
	
	return 0;
}


//��moveLָ��ת��ΪABB�п���ʶ����ַ�����extaxis����������
string Use_Abb_Beckhoff::encodeInstruction(robtarget targetPoint)
{
	string ret="1";
	string temp;
	//�Ƚ�pose��Ϣת��
	int i;
	for (i=0; i<7; i++)
	{
		temp=to_string(targetPoint.pose[i]);
		temp=temp.substr(0,temp.size()-3); //������λС��
		ret=ret+ ' ' + temp;
	}
	//�ٽ�confDataת��
	for (i=0; i<4; i++)
	{
		ret=ret+ ' ' + to_string(targetPoint.confData[i]);
	}

	ret = ret + ' ' + '#';
	return ret;
};

int Use_Abb_Beckhoff::movelABB(robtarget targetPoint) //��connect֮��movel��һ���㣬�������Ƿ�ɹ����д���Ϊ1��û����Ϊ0�����Ϊ2
{
	//Maxium 80 Characters can be send one time

	string temp = Use_Abb_Beckhoff::encodeInstruction(targetPoint);  //��targetpointת��Ϊ�ַ���  
	char instructionSend[80];
	strcpy_s(instructionSend, temp.c_str());  // Ҳ���Դ�temp
	//CHAR szSend[100] = "1 900 0 1300 0.424 -0.451 0.760 -0.195 #";   //�ͻ���  �ȷ�����
	int numsend=send(sockclientABB,instructionSend,sizeof(instructionSend),0);  //���ͺ���������ͨ������ֵ�жϷ��ͳɹ����
	if (numsend == 0)
	{
		WSAGetLastError();
		return 1;
		errorCode="Send to ABB error\n";
	}
	printf("Move to:\n");
	printf(temp.c_str());
	//���շ������ش�������,��ʾ�ɹ��˶����ص�
	char szRecv[100] = {0};
	int numrecv=recv(sockclientABB,szRecv,100,0); //���պ���
	if (numrecv <= 0)
	{
		return 1;
		errorCode="Receive from ABB error\n";
	};
	printf("%s\n",szRecv);  //��ʾ���ַ����ĸ�ʽ����������˷��͵����ݡ�
	//  getch();//��ͣһ��
	//�ر�socket, ����Ҫclose��һֱ����20190712
	//closesocket(sockclientABB);
	return 0;
}




//EularAngle to Quaternion according to the order of 3-2-1, i.e.: psi, theta, phi
int Use_Abb_Beckhoff::euler2Quater(double* eulerAngle, double* quaternion)
{
	double phi, theta, psi;
	//double q1, q2, q3, q4;
	phi=eulerAngle[0];
	theta=eulerAngle[1];
	psi=eulerAngle[2];
	quaternion[0] = cos(phi/2)*cos(theta/2)*cos(psi/2)+sin(phi/2)*sin(theta/2)*sin(psi/2);
	quaternion[1] = sin(phi/2)*cos(theta/2)*cos(psi/2)-cos(phi/2)*sin(theta/2)*sin(psi/2);
	quaternion[2] = cos(phi/2)*sin(theta/2)*cos(psi/2)+sin(phi/2)*cos(theta/2)*sin(psi/2);
	quaternion[3] = cos(phi/2)*cos(theta/2)*sin(psi/2)-sin(phi/2)*sin(theta/2)*cos(psi/2);
	return 0; 
};

int Use_Abb_Beckhoff::parseBeckhoffData(string msgBeckhoff,int* beckhoffData) //return to the number of datas
{
	int beckhoffDataNum;
	int length;		//length of the string
	int ind1=0;		//initial location of the para
	int ind2=0;		//tail location of the para
	int i=0;
	length=msgBeckhoff.find('#');
	while (ind2<length-1)
	{
		ind1=ind2;
		ind2=msgBeckhoff.substr(ind2+1).find(' ')+ind2+1;   //find the next blank
		if (ind1==0)
		{
			beckhoffData[i]=atoi(msgBeckhoff.substr(ind1,ind2-ind1).c_str());
		}
		else
		{
			beckhoffData[i]=atoi(msgBeckhoff.substr(ind1+1,ind2-ind1-1).c_str());
		}
		i=i+1;
	};
	beckhoffDataNum=i;
	return beckhoffDataNum;

};

int Use_Abb_Beckhoff::dataInt2Double(int* beckhoffData, double* beckhoffDataDouble) //The problem was solved on 2019.11.21
{
	int i;
	int k=0;
	double voltage;

	for (i=0; i<4; i++)
	{
		//CCD 1-4, with the range of HC1100. The dianominator was changed to 18383, because EL3068 is 0~10V but the output of the CCD is 0~5V
		voltage=beckhoffData[i]*5.0/16383.0;
		if (voltage > 5.18)
		{
			beckhoffDataDouble[i]=0.001; //Exceed the range of the CCD;
			//debug
			//printf("CCD %f is out of range!", i+1);
		}
		else
		{
			beckhoffDataDouble[i]=135.0-(beckhoffData[i]/16383.0*70.0);  //distance of CCD, unit:mm
		}
		k=k+1;
	};

	for (i=0; i<4; i++)
	{
		//CCD 5-8, with the range of HC1200
		voltage=beckhoffData[i+4]*5.0/16383.0;
		if (voltage > 5.18)
		{
			beckhoffDataDouble[i+4]=0.001; //Exceed the range of the CCD;
			//debug
			//printf("CCD %d is out of range!", i+5);
		}
		else
		{
			beckhoffDataDouble[i+4]=280.0-(beckhoffData[i+4]/16383.0*160.0);  //distance of CCD, unit:mm
		}
		k=k+1;
	};

	for (i=0; i<8; i++)
	{
		//CCD 13-20, with the type of HC1030
		voltage=beckhoffData[i+8]*5.0/16383.0;
		if (voltage > 5.18)
		{
			beckhoffDataDouble[i+8]=0.001; //Exceed the range of the CCD;
			//debug
			//printf("CCD %d is out of range!", i+13);
		}
		else
		{
			beckhoffDataDouble[i+8]=135.0-(beckhoffData[i+8]/16383.0*70.0);  //distance of CCD, unit:mm
		}
		k=k+1;
	};

	for (i=0; i<12; i++)
	{
		//PSD
		//If you look directly at the PSD, right is positive
		beckhoffDataDouble[i+16]=(beckhoffData[16+i*2]*1.0)*10.0/(beckhoffData[17+i*2]*1.0+0.001);  //distance of PSD, unit:mm "+0.001" is for test
		k=k+1;
	};
	for (i=0; i<2; i++)
	{
		//Grandienter: some of its code is in MATLAB.
		//for this program, grandienter data is temporarily unused
		beckhoffDataDouble[i+28]=(beckhoffData[40+i]-16383)*30.0/32767.0;  //unit: degree
		k=k+1;
	};
	for (i=0; i<4; i++)
	{
		//CCD 9-12, with the type of HC1200
		voltage=beckhoffData[i+42]*5.0/16383.0;
		if (voltage > 5.18)
		{
			beckhoffDataDouble[i+30]=0.001; //Exceed the range of the CCD;
			//debug
			//printf("CCD %d is out of range!", i+9);
		}
		else
		{
			beckhoffDataDouble[i+30]=280.0-(beckhoffData[i+42]/16383.0*160.0);  //distance of CCD, unit:mm
		}
		k=k+1;
	};
	// According to the clb experiment in 20191111, some data should be alternated
	//beckhoffDataDouble[7] = beckhoffDataDouble[7]-0.6; //ccd8-0.6
	//beckhoffDataDouble[32] = beckhoffDataDouble[32]+0.6;  //ccd11+0.6

	return k;//number of the datas;
};

int Use_Abb_Beckhoff::suckerAction(int action)
{
	char instructionSend[80];  // instruction to be send to Beckhoff
	int numsend;  // number of the chars sent
	int numrecv;  // number of the chars received
	char szRecv[255] = {0}; // Received chars from Beckhoff to decide whether action was done
	/*2 cases*/
	switch (action)
	{
	case SUCK:
		strcpy_s(instructionSend, "Suck");
		//CHAR szSend[100] = "1 900 0 1300 0.424 -0.451 0.760 -0.195 #";   //�ͻ���  �ȷ�����
		numsend=send(sockclientBeckhoff,instructionSend,sizeof(instructionSend),0);  //���ͺ���������ͨ������ֵ�жϷ��ͳɹ����
		if (numsend == 0)
		{
			WSAGetLastError();
			errorCode= "Send instruction to Beckhoff Error!\n";
			printf("Send instruction to Beckhoff Error!\n");
			return 1;
		}
		//���շ������ش�������

		numrecv=recv(sockclientBeckhoff,szRecv,255,0); //���պ���
		if (numrecv == SOCKET_ERROR)
		{
			printf("Receive suck successful signal from Beckhoff Error!\n. Error code = %d\n", WSAGetLastError());
			errorCode= "Receive suck successful signal from Beckhoff Error!\n";

			return 1;
		}
		printf("%s\n",szRecv); 
		//_getch();//��ͣһ��
		return 0;

	case RELEASE:
		strcpy_s(instructionSend, "Release");

		numsend=send(sockclientBeckhoff,instructionSend,sizeof(instructionSend),0);  //���ͺ���������ͨ������ֵ�жϷ��ͳɹ����
		if (numsend == 0)
		{
			WSAGetLastError();
			errorCode= "Send instruction to Beckhoff Error!\n";
			return 1;
		}
		//���շ������ش�������
		numrecv = recv(sockclientBeckhoff,szRecv,255,0); //���պ���
		if (numrecv == SOCKET_ERROR)
		{
			WSAGetLastError();
			errorCode= "Receive release successful signal from Beckhoff Error!\n";
			return 1;
		}
		printf("%s\n.",szRecv); 
		//_getch();//��ͣһ��
		return 0;

	}
};

int Use_Abb_Beckhoff::ceramicInEf(double* beckhoffDataDouble, double* poseCrmcInEf, clbdata clbData)
{
	//Already checked
	double efInFrame[3];    //pose of ef in the frame, 3DOF. Not using anymore
	double frameInEf[3];    //pose of the frame in Ef. Means that the CS of Ef firstly moves along its XY axis by dx and dy. Then rotate around its Z axis by dtheta to coincident with the CS of the Frame.
	double crmcInFrame[3];  //pose of ceramic in the frame

	/**/
	double l=582.6;				//distance between the ccds in the frame: mm
	double d=800;				//width of the ceramic: mm

	/***************/
	/* crmcInFrame */
	/***************/
	double dCcd13, dCcd14, dCcd15, dCcd16, dCcd17, dCcd18, dCcd19, dCcd20;   //new-old
	dCcd13=beckhoffDataDouble[8]-clbData.ceramicData[0];// Present data - calibration data to get the relative data
	dCcd14=beckhoffDataDouble[9]-clbData.ceramicData[1];
	dCcd15=beckhoffDataDouble[10]-clbData.ceramicData[2];
	dCcd16=beckhoffDataDouble[11]-clbData.ceramicData[3];
	dCcd17=beckhoffDataDouble[12]-clbData.ceramicData[4];
	dCcd18=beckhoffDataDouble[13]-clbData.ceramicData[5];
	dCcd19=beckhoffDataDouble[14]-clbData.ceramicData[6];
	dCcd20=beckhoffDataDouble[15]-clbData.ceramicData[7];
	double a13, a14, a15, a16, a17, a18, a19, a20;
	/*a13 to a20 need to be measured accurately!!!!*/
	a13=l/2; a14=l/2; a15=l/2; a16=l/2; a17=l/2; a18=l/2; a19=l/2; a20=l/2;  //laser point offset in the CS of ef
	double p41[2],p12[2],p23[2],p34[2]; //2
	lXing(a13,d/2-dCcd13,-a14,d/2-dCcd14,d/2-dCcd19,-a19,d/2-dCcd20,a20,p41);
	lXing(a13,d/2-dCcd13,-a14,d/2-dCcd14,-d/2+dCcd15,a15,-d/2+dCcd16,-a16,p12);
	lXing(-d/2+dCcd15,a15,-d/2+dCcd16,-a16,-a17,-d/2+dCcd17,a18,-d/2+dCcd18,p23); //wrong function lxing can not avoid INF
	lXing(-a17,-d/2+dCcd17,a18,-d/2+dCcd18,d/2-dCcd19,-a19,d/2-dCcd20,a20,p34);
	/*position offset*/
	//��ӡ�ǵ������
	printf("P41 coordinate is [%f mm, %f mm]\n", p41[0],p41[1]);
	printf("P12 coordinate is [%f mm, %f mm]\n", p12[0],p12[1]);
	printf("P23 coordinate is [%f mm, %f mm]\n", p23[0],p23[1]);
	printf("P34 coordinate is [%f mm, %f mm]\n", p34[0],p34[1]);
	// There must be sth wrong in this part
	lXing((p41[0]+p12[0])/2,(p41[1]+p12[1])/2,(p23[0]+p34[0])/2,(p23[1]+p34[1])/2,(p12[0]+p23[0])/2,(p12[1]+p23[1])/2,(p41[0]+p34[0])/2,(p41[1]+p34[1])/2,crmcInFrame);
	//�����ĵ���е�ķ�ʽ,�����ܲ��������Ĺۣ�����ǵȼ۵ġ������ܼ򻯼��㣬��������������ϸ�
	crmcInFrame[0] = (p41[0]+p12[0]+p23[0]+p34[0])/4; //x
	crmcInFrame[1] = (p41[1]+p12[1]+p23[1]+p34[1])/4; //y
	/*orientation offset*/
	crmcInFrame[2]=(atan((-dCcd13+dCcd14)/(a13+a14))+atan((-dCcd15+dCcd16)/(a15+a16))+atan((-dCcd17+dCcd18)/(a17+a18))+atan((-dCcd19+dCcd20)/(a19+a20)))/4;
	double temp1, temp2, temp3, temp4;
	temp1 = atan((-dCcd13+dCcd14)/(a13+a14));
	temp2 =	atan((-dCcd15+dCcd16)/(a15+a16));
	temp3 = atan((-dCcd17+dCcd18)/(a17+a18));
	temp4 = atan((-dCcd19+dCcd20)/(a19+a20));
	printf("The coordinate of ceramic in Frame is x = %f mm, y= %f mm, theta= %f rad\n",crmcInFrame[0],crmcInFrame[1],crmcInFrame[2]);
	//_getch();
	/***********************************************/
	/* efInFrame rewritten in 20191030, use 8 CCDs */
	/***********************************************/
	// Define the current readings of the CCD
	double ccd5, ccd6, ccd7, ccd8, ccd9, ccd10, ccd11, ccd12;
	ccd5=beckhoffDataDouble[4];
	ccd6=beckhoffDataDouble[5];
	ccd7=beckhoffDataDouble[6];
	ccd8=beckhoffDataDouble[7];
	ccd9=beckhoffDataDouble[30];
	ccd10=beckhoffDataDouble[31];
	ccd11=beckhoffDataDouble[32];
	ccd12=beckhoffDataDouble[33];
	// Define the calibration readings of the CCD, named as clbCCD
	double clbCCD5, clbCCD6, clbCCD7, clbCCD8, clbCCD9, clbCCD10, clbCCD11, clbCCD12;
	clbCCD5=clbData.efData[0];
	clbCCD6=clbData.efData[1];
	clbCCD7=clbData.efData[2];
	clbCCD8=clbData.efData[3];
	clbCCD9=clbData.efData[4];
	clbCCD10=clbData.efData[5];
	clbCCD11=clbData.efData[6];
	clbCCD12=clbData.efData[7];


	// Calculate the dtheta
	double dtheta[4]; //Define 4 dthetas
	// Define the distance between the CCD laser beam and the center line
	double a, a5, a6, a7, a8, a9, a10, a11, a12;
	a=137.7; a5=137.7; a6=137.7; a7=137.7; a8=137.7; a9=137.7; a10=137.7; a11=137.7; a12=137.7;
	//a = 133;
	// Calculate the angle
	dtheta[0] = -atan(((ccd6-clbCCD6)-(ccd5-clbCCD5))/(2*a));  //��4�������ش���,�ѽ��
	dtheta[1] = -atan(((ccd8-clbCCD8)-(ccd7-clbCCD7))/(2*a));
	dtheta[2] = -atan(((ccd10-clbCCD10)-(ccd9-clbCCD9))/(2*a));
	dtheta[3] = -atan(((ccd12-clbCCD12)-(ccd11-clbCCD11))/(2*a));
	double dTheta;
	dTheta = 0.25*(dtheta[0]+dtheta[1]+dtheta[2]+dtheta[3]); //����theta��Ҫ��Ϊ���ģ� ��Ϊ���µĹ�ʽ�У��Ƕȶ���Ϊ��efת��ref����Ҫ�ĽǶȡ�
	frameInEf[2] = dTheta;

	// Calculate the position ofst
	double A5, A6, A7, A8, A9, A10, A11, A12;  // Middle variable
	double B5, B6, B7, B8, B9, B10, B11, B12;  // Middle variable 
	double dF=915.0; // Width of the frame

	//Calculate the middle variables(B matrix), these variables are re-derived
	A5 = -(cos(dTheta)*(dF/2.0-clbCCD5)-sin(dTheta)*a-dF/2.0)-cos(dTheta)*ccd5;
	B5 = -(-sin(dTheta)*(dF/2.0-clbCCD5)-cos(dTheta)*a+1.0/cos(dTheta)*(sin(dTheta)*dF/2.0+a))+sin(dTheta)*ccd5; 

	A6 = -(cos(dTheta)*(dF/2.0-clbCCD6)+sin(dTheta)*a-dF/2.0)-cos(dTheta)*ccd6;
	B6 = -(-sin(dTheta)*(dF/2.0-clbCCD6)+cos(dTheta)*a+1.0/cos(dTheta)*(sin(dTheta)*dF/2.0-a))+sin(dTheta)*ccd6; 

	A7 = -(cos(dTheta)*a+sin(dTheta)*(dF/2.0-clbCCD7)-1.0/cos(dTheta)*(sin(dTheta)*dF/2.0+a))-sin(dTheta)*ccd7;
	B7 = -(-sin(dTheta)*a+cos(dTheta)*(dF/2.0-clbCCD7)-dF/2.0)-cos(dTheta)*ccd7; 

	A8 = -(-cos(dTheta)*a+sin(dTheta)*(dF/2.0-clbCCD8)-1.0/cos(dTheta)*(sin(dTheta)*dF/2.0-a))-sin(dTheta)*ccd8;
	B8 = -(sin(dTheta)*a+cos(dTheta)*(dF/2.0-clbCCD8)-dF/2.0)-cos(dTheta)*ccd8; 

	A9 = -(-cos(dTheta)*(dF/2.0-clbCCD9)+sin(dTheta)*a+dF/2.0)+cos(dTheta)*ccd9;
	B9 = -(sin(dTheta)*(dF/2.0-clbCCD9)+cos(dTheta)*a+1.0/cos(dTheta)*(sin(dTheta)*(-dF/2.0)-a))-sin(dTheta)*ccd9; 

	A10 = -(-cos(dTheta)*(dF/2.0-clbCCD10)-sin(dTheta)*a+dF/2.0)+cos(dTheta)*ccd10;
	B10 = -(sin(dTheta)*(dF/2.0-clbCCD10)-cos(dTheta)*a+1.0/cos(dTheta)*(sin(dTheta)*(-dF/2.0)+a))-sin(dTheta)*ccd10; 

	A11 = -(-cos(dTheta)*a-sin(dTheta)*(dF/2.0-clbCCD11)-1.0/cos(dTheta)*(sin(dTheta)*(-dF/2.0)-a))+sin(dTheta)*ccd11;
	B11 = -(sin(dTheta)*a-cos(dTheta)*(dF/2.0-clbCCD11)+dF/2.0)+cos(dTheta)*ccd11; 

	A12 = -(cos(dTheta)*a-sin(dTheta)*(dF/2.0-clbCCD12)-1.0/cos(dTheta)*(sin(dTheta)*(-dF/2.0)+a))+sin(dTheta)*ccd12;
	B12 = -(-sin(dTheta)*a-cos(dTheta)*(dF/2.0-clbCCD12)+dF/2.0)+cos(dTheta)*ccd12; 


	// Define the matrix
	double A[32]={
		-cos(dTheta), -sin(dTheta),
		sin(dTheta), sin(dTheta)*tan(dTheta),
		-cos(dTheta), -sin(dTheta),
		sin(dTheta), sin(dTheta)*tan(dTheta),

		sin(dTheta)*tan(dTheta), -sin(dTheta),
		sin(dTheta), -cos(dTheta),
		sin(dTheta)*tan(dTheta), -sin(dTheta),
		sin(dTheta), -cos(dTheta),

		-cos(dTheta), -sin(dTheta),
		sin(dTheta), sin(dTheta)*tan(dTheta),
		-cos(dTheta), -sin(dTheta),
		sin(dTheta), sin(dTheta)*tan(dTheta),

		sin(dTheta)*tan(dTheta), -sin(dTheta),
		sin(dTheta), -cos(dTheta),
		sin(dTheta)*tan(dTheta), -sin(dTheta),
		sin(dTheta), -cos(dTheta)
	};
	// A: 16 rows, 2 columns
	double B[16]={
		A5,
		B5,
		A6,
		B6,
		A7,
		B7,
		A8,
		B8,
		A9,
		B9,
		A10,
		B10,
		A11,
		B11,
		A12,
		B12
	};//B: 16 rows, 1 column

	//Start calculation
	double *temp = new double[4]; 
	double *tA = new double[32];
	double *invtemp = new double[4]; 
	double *tAB = new double[2];

	mathmatica::matrixTrans(tA,A,16,2); //tA=A'
	mathmatica::matrixMultiply(temp,2,2,tA,2,16,A,16,2);  // tA*A
	mathmatica::matrixInverse2(invtemp,temp);	// invtemp = inv(tA*A)
	mathmatica::matrixMultiply(tAB,2,1,tA,2,16,B,16,1); // tAB = tA*B
	mathmatica::matrixMultiply(frameInEf,2,1,invtemp,2,2,tAB,2,1);	// frameInEf[0~1]=inv(tA*A)*tA*B

	delete [] temp;
	delete [] tA;
	delete [] tAB;
	delete [] invtemp;

	// Current frameInEf is not expressed in WCS (EF CS), so they need to be transformed to WCS.
	double tFrameInEf;
	tFrameInEf=frameInEf[0]; 
	frameInEf[0] = frameInEf[1];  // dxw=dy
	frameInEf[1] = -tFrameInEf;   // dyw=-dx
	printf("The coordinate of the frame in EF is x = %f mm, y= %f mm, theta= %f rad\n",frameInEf[0],frameInEf[1],frameInEf[2]);

	/*Calculate how to express the pose of the crmc in the corrdinate of the EF*/
	// Sequence: from the CS of Ef to to the CS of crmc. Firstly, move the CS of the Ef along its own X and Y axes by [1] and [2], respectively.
	// Then rotate around  its own Z axis by [3] (rad).
	// The drivation is in the notebook 
	poseCrmcInEf[0]=cos(frameInEf[2])*(crmcInFrame[0])-sin(frameInEf[2])*(crmcInFrame[1])+frameInEf[0];
	poseCrmcInEf[1]=sin(frameInEf[2])*(crmcInFrame[0])+cos(frameInEf[2])*(crmcInFrame[1])+frameInEf[1];
	poseCrmcInEf[2]=frameInEf[2]+crmcInFrame[2];

	return 0;
};

/*try to use malloc? No, waste*/
int Use_Abb_Beckhoff::lXing(double x11,double y11,double x12,double y12,double x21,double y21,double x22,double y22,double *retP)
{
	/*new calculation method, avoid*/
	double a1,b1,c1,a2,b2,c2;
	a1=y12-y11;
	b1=-(x12-x11);
	c1=x11*(y12-y11)-y11*(x12-x11);
	a2=y22-y21;
	b2=-(x22-x21);
	c2=x21*(y22-y21)-y21*(x22-x21);
	if (a1*b2-b1*a2 !=0 )
	{
		retP[0]=(b2*c1-b1*c2)/(a1*b2-b1*a2);
		retP[1]=(-a2*c1+a1*c2)/(a1*b2-b1*a2);
		return 0;
	}
	else
	{
		return 1;
		printf ("wrong ccd value!");
		_getch();
	}

};

int Use_Abb_Beckhoff::lCntrXing(double x11,double y11,double a1,double x12,double y12,double a2,double x21,double y21,double a3,double x22,double y22,double a4,double *cp)
{
	/*improved method*/
	double cpL1[2];
	double cpL2[2];
	cpL1[0]=x11+(x12-x11)*a1/(a1+a2);
	cpL1[1]=y11+(y12-y11)*a1/(a1+a2);
	cpL2[0]=x21+(x22-x21)*a3/(a3+a4);
	cpL2[1]=y21+(y22-y21)*a3/(a3+a4);
	double a_1,b_1,c_1,a_2,b_2,c_2;
	a_1=x12-x11;
	b_1=-(y12-y11);
	c_1=(x12-x11)*cpL1[0]-(y12-y11)*cpL1[1];
	a_2=x22-x21;
	b_2=-(y22-y21);
	c_2=(x22-x21)*cpL1[0]-(y22-y21)*cpL1[1];

	cp[0]=(b_2*c_1-b_1*c_2)/(a_1*b_2-b_1*a_2);
	cp[1]=(-a_2*c_1+a_1*c_2)/(a_1*b_2-b_1*a_2);
	return 0;
};

int Use_Abb_Beckhoff::moveContPoints(int numPoints)
{
	for (int i=0; i<numPoints; i=i+1)
	{
		/*Move to the target*/
		printf("Gonna move to [%f mm, %f mm, %f mm]. Press any buttom (once!) to continue...\n", abbRobtargetList5[i].pose[0], abbRobtargetList5[i].pose[1], abbRobtargetList5[i].pose[2]);
		//_getch();		//pause
		manipulateRobot(TRAVEL, MOVEL, abbRobtargetList5[i]);

	}
	return 0;
};

int Use_Abb_Beckhoff::getEfOfstInRef()//Calculate the dx,dy,dtheta.
{
	//Already checked
	/*The result will be transferred to EfOfstInRef[3]; [dx,dy,dtheta]*/
	//dx,dy,dtheta. Meaning that the RCS(Reference coordinate system) 
	//firstly move along its own axes for dx and dy
	//than rotate around its new z axis for dtheta to coincident with Ef

	/*Firstly get the PSD data from beckhoffDataDouble[30]*/
	//const double ofstPSD9=0.0, ofstPSD10=0.0, ofstPSD11=0.0, ofstPSD12=0.0; //PSD readings when the Ef was exactly coincident with the laser
	//Before calibration, all the offset are equal to zero

	double PSD9, PSD10, PSD11, PSD12;  //Current PSD readings - PSD offset = "actual PSD readings"
	PSD9 =beckhoffDataDouble[24]-clbData.psdData[8];  //PSD readings when the Ef was exactly aligned with the laser
	PSD10=beckhoffDataDouble[25]-clbData.psdData[9];
	PSD11=beckhoffDataDouble[26]-clbData.psdData[10];
	PSD12=beckhoffDataDouble[27]-clbData.psdData[11];
	double dx, dy, dtheta; //define output
	const double D9=279.0,D10=279.0,D11=279.0,D12=279.0; //Define the distance between PSD and the center of the Ef
	/*Detailed derivation is in the notebook*/
	dtheta=atan(-0.5*(PSD9+PSD11)/(D9+D11)-0.5*(PSD10+PSD12)/(D10+D12));
	dy=0.5*(cos(dtheta)*(PSD11-PSD9)+sin(dtheta)*(D11-D9));
	dx=0.5*(cos(dtheta)*(PSD10-PSD12)+sin(dtheta)*(D10-D12));
	EfOfstInRef[0]=dx;
	EfOfstInRef[1]=dy;
	EfOfstInRef[2]=dtheta;	
	return 0;
}

int Use_Abb_Beckhoff::getCrmcOfstInRef()//Calculate the dx,dy,dtheta.
{
	//Calculate the dx,dy,dtheta of CrmcOfstInRef[3] from EfOfstInRef[3] and poseCrmcInEf[3]
	/*The result will be transferred to CrmcOfstInRef[3]; [dx,dy,dtheta]*/
	//dx,dy,dtheta. Meaning that the RCS(Reference coordinate system) 
	//firstly move along its own axes for dx and dy
	//than rotate around its new z axis for dtheta to coincident with CS of Crmc

	/*detailed derivation is in the notebook*/
	double dx_ec,dy_ec,dtheta_ec;
	double dx_re,dy_re,dtheta_re;
	dx_re=EfOfstInRef[0];
	dy_re=EfOfstInRef[1];
	dtheta_re=EfOfstInRef[2];
	dx_ec=poseCrmcInEf[0];
	dy_ec=poseCrmcInEf[1];
	dtheta_ec=poseCrmcInEf[2];
	/*dx*/
	CrmcOfstInRef[0]=dx_ec*cos(dtheta_re)-dy_ec*sin(dtheta_re)+dx_re;
	/*dy*/
	CrmcOfstInRef[1]=dx_ec*sin(dtheta_re)+dy_ec*cos(dtheta_re)+dy_re;
	/*dtheta*/
	CrmcOfstInRef[2]=dtheta_re+dtheta_ec;
	return 0;

	//So, if want to move the crmc to the REF in the CS of the EF(or robot when CS of the Ef is parallel with WCS),
	//firstly, rotate around the Z axis by -CrmcOfstInRef[2];
	//Then move along the x and y axes by -CrmcOfstInRef[0] and -CrmcOfstInRef[1].


}

int Use_Abb_Beckhoff::correctPose()
{
	//Already checked instead of the quarternion
	//under construction, need to be double check
	//But, we need the pose of the RCS (laser) in the WCS (robot).
	//So, the above CrmcOfstInRef[3] need to be transferred. The specific moving details are in the notebook.
	//Apart from the CrmcOfstInRef[3], thetaWCS2Ef is also need.
	abbRobtarget=lastAbbRobtarget; //transfer the data first, just in case
	double x_ce=poseCrmcInEf[0], y_ce=poseCrmcInEf[1], theta_ce=poseCrmcInEf[2];  //poseCrmcInEf[3]. details are in the note book
	double x_er=EfOfstInRef[0], y_er=EfOfstInRef[1], theta_er=EfOfstInRef[2];  //EfOfstInRef[3]
	/*
	//20191121���ԣ�����������㣬�Ϳ��ڵ���������
	x_ce=0.0;
	y_ce=0.0;
	theta_ce=0.0;
	*/

	//20191115���ԣ�����û�м��������¾������ for paper
	x_er=0.0;
	y_er=0.0;
	theta_er=0.0;


	double x_re, y_re, theta_re;  //refInEf[3]
	x_re=-x_er*cos(theta_er)-y_er*sin(theta_er);
	y_re=x_er*sin(theta_er)-y_er*cos(theta_er);
	theta_re=-theta_er;

	// Last pose
	double x_l,y_l,theta_l;
	x_l=lastAbbRobtarget.pose[0];
	y_l=lastAbbRobtarget.pose[1];
	theta_l=lastAbbRobtarget.pose[2];

	// Distance and the angle that Ef should move along the WCS
	double dx, dy, theta;
	theta = theta_re-theta_ce;//+thetaWCS2Ef;
	double x_ce_, y_ce_;
	x_ce_=cos(theta)*x_ce-sin(theta)*y_ce;
	y_ce_=sin(theta)*x_ce+cos(theta)*y_ce;

	dx = x_re-x_ce_;
	dy = y_re-y_ce_;


	// Calculation of the quarternion details are in the notebook
	abbRobtarget.pose[0]=dx+x_l;    //x Axis
	abbRobtarget.pose[1]=dy+y_l;	//y Axis
	abbRobtarget.pose[4]=sqrt(1.0/(1.0+tan(theta/2)*tan(theta/2)))*tan(theta/2);  //q2
	abbRobtarget.pose[5]=-sqrt(1.0/(1.0+tan(theta/2)*tan(theta/2)));  //q3

	// Some safty codes are essential
	if (dx > 20 || dy > 20 || theta > 0.3 || dx < -20 || dy < -20 || theta < -0.3){
		abbRobtarget.pose[0]=10+x_l;    //x Axis
		abbRobtarget.pose[1]=10+y_l;	//y Axis
		abbRobtarget.pose[4]=0;  //q2
		abbRobtarget.pose[5]=-1;  //q3
	}
	return 0;
}