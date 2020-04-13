#include "stdafx.h"
#include "Egm.h"
#include "conio.h"
Egm::Egm(string szIP, unsigned int nPort)
{
	szAddrPC = szIP;
	nPortNumber = nPort;

	nSequenceNumber = 0;  // Initialize senquence number
	/* Init winsock */
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		fprintf(stderr, "Could not open Windows connection.\n");
		exit(0);
	}

	// create socket to listen on
	sockegm = ::socket(AF_INET,SOCK_DGRAM,0);

	memset(&serverAddr, sizeof(serverAddr), 0);
	serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_addr.s_addr = inet_addr(szAddrPC.c_str());
	serverAddr.sin_port = htons(nPortNumber);

	// listen on all interfaces
	bind(sockegm, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
}

void Egm::CreateAndSendSensorMessage()
{
	EgmSensor *pSensorMessage = new EgmSensor();
	EgmHeader* header = new EgmHeader();
	header->set_mtype(EgmHeader_MessageType_MSGTYPE_CORRECTION);
	header->set_seqno(nSequenceNumber++);
	header->set_tm(GetTickCount());

	pSensorMessage->set_allocated_header(header);

	EgmCartesian *pc = new EgmCartesian();
	pc->set_x(posePlanned.pos.x);
	pc->set_y(posePlanned.pos.y);
	pc->set_z(posePlanned.pos.z);

	EgmQuaternion *pq = new EgmQuaternion();
	pq->set_u0(posePlanned.ori.q1);
	pq->set_u1(posePlanned.ori.q2);
	pq->set_u2(posePlanned.ori.q3);
	pq->set_u3(posePlanned.ori.q4);

	//EgmEuler *pe = new EgmEuler();
	//pe->set_x(1.2/57.1);
	//pe->set_y(0.0);
	//pe->set_z(0.0);

	EgmPose *pcartesian = new EgmPose();
	pcartesian->set_allocated_orient(pq);
	pcartesian->set_allocated_pos(pc);
	//pcartesian->set_allocated_euler(pe);

	EgmPlanned *planned = new EgmPlanned();
	planned->set_allocated_cartesian(pcartesian);

	if (pSensorMessage->planned().cartesian().pos().x()>100 || pSensorMessage->planned().cartesian().pos().y()>100 || pSensorMessage->planned().cartesian().pos().z()>100){
		printf("too far!");
		_getch();
	}
	pSensorMessage->set_allocated_planned(planned);
	printf("Planned to x=%f y=%f z=%f, q1=%f, q2=%f, q3=%f, q4=%f\n", pSensorMessage->planned().cartesian().pos().x(), pSensorMessage->planned().cartesian().pos().y(), pSensorMessage->planned().cartesian().pos().z(), pSensorMessage->planned().cartesian().orient().u0(), pSensorMessage->planned().cartesian().orient().u1(), pSensorMessage->planned().cartesian().orient().u2(), pSensorMessage->planned().cartesian().orient().u3());
	pSensorMessage->SerializeToString(&szMessageBuffer);

	// send a message to the robot
	n = sendto(sockegm, szMessageBuffer.c_str(), szMessageBuffer.length(), 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
	if (n < 0)
	{
		printf("Error send message\n");
	}
	delete pSensorMessage;
}

int Egm::FetchRobotMessage()
{
	iLenAddr = sizeof(clientAddr);
	n = recvfrom(sockegm, chProtoMessage, 1400, 0, (struct sockaddr *)&clientAddr, &iLenAddr);
	if (n < 0)
	{
		//printf("Error receive message\n");
		return -1;
	}

	// deserialize inbound message
	EgmRobot *pRobotMessage = new EgmRobot();  //Received Message from the Robot (Deserialized).
	pRobotMessage->ParseFromArray(chProtoMessage, n);
	/*Do whatever you wanted to do after parsing the message*/
	if (pRobotMessage->has_header() && pRobotMessage->header().has_seqno() && pRobotMessage->header().has_tm() && pRobotMessage->header().has_mtype())
	{
		poseFeedback.pos.x = pRobotMessage->feedback().cartesian().pos().x();
		poseFeedback.pos.y = pRobotMessage->feedback().cartesian().pos().y();
		poseFeedback.pos.z = pRobotMessage->feedback().cartesian().pos().z();
		poseFeedback.ori.q1 = pRobotMessage->feedback().cartesian().orient().u0();
		poseFeedback.ori.q2 = pRobotMessage->feedback().cartesian().orient().u1();
		poseFeedback.ori.q3 = pRobotMessage->feedback().cartesian().orient().u2();
		poseFeedback.ori.q4 = pRobotMessage->feedback().cartesian().orient().u3();
		nSeqNoRob = pRobotMessage->header().seqno();

		printf("SeqNoRob=%d q1Rob=%f q2Rob=%f q3Rob=%f q4Rob=%f.\n", pRobotMessage->header().seqno(), poseFeedback.ori.q1, poseFeedback.ori.q2, poseFeedback.ori.q3, poseFeedback.ori.q4);

	}
	else
	{
		printf("No header\n");
	}

	delete pRobotMessage;  //Free memory
	return n;
}

void Egm::CalculatePlannedPose()
{
	/*Replace it by your own method*/
	posePlanned.pos.x = 1402.0;
	posePlanned.pos.y = 50.0;
	posePlanned.pos.z = 802.0;
	posePlanned.ori.q1 = 1.0;
	posePlanned.ori.q2 = 0.0;
	posePlanned.ori.q3 = 0.0;
	posePlanned.ori.q4 = 0.0;
}
