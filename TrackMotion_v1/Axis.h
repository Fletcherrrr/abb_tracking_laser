#pragma once

#include <windows.h>
/**************************************�궨��**************************************/
/*���ٵȼ�*/
#define TRACE_LEVEL0				0
#define TRACE_LEVEL1				1
/*���״̬��־����*/
#define ES_UVLO						0   //Ƿѹ
#define ES_BERR					    1   //B�����
#define ES_AERR					    2   //A�����
#define ES_BOC					    3   //B�����
#define ES_AOC					    4   //A�����
#define ES_OTS					    5   //���ȱ���
/*������״̬��־����*/
#define CS_EXT1						0	//�ⲿֹͣ1
#define CS_EXT2						1	//�ⲿֹͣ2
#define CS_STALL					2	//��ת��־
#define CS_BUSY						3	//æ��־
#define CS_EXT3						4	//�ⲿֹͣ3
#define CS_PVT3_FIFO_EMPTY			5	//PVTģʽ3��FIFOΪ��
#define CS_PVT3_LOW_THRESHOLD		6	//PVTģʽ3��FIFO��ȵ�������
#define CS_PVT3_HIGH_THRESHOLD		7	//PVTģʽ3��FIFO��ȸ�������

/*ϸ�ֶ���*/
#define MS_0						0	//0ϸ��
#define MS_2						2	//2ϸ��
#define MS_4						4	//4ϸ��
#define MS_8						8	//8ϸ��
#define MS_16						16	//16ϸ��
#define MS_32						32	//32ϸ��
#define MS_64						64	//64ϸ��
#define MS_128						128	//128ϸ��
#define MS_256						256	//256ϸ��
/*����ģʽ����*/
#define WM_POS						0	//λ��ģʽ
#define WM_VELOCITY					1	//�ٶ�ģʽ
#define WM_PVT						2	//PVTģʽ
#define WM_ENC_FOLLOW				3	//����������ģʽ
/*ת��������*/
#define MOTOR_FORWARD				1	//����ת��
#define MOTOR_REVERSE				0	//����ת��
/*�ⲿֹͣ����*/
#define	EXT_STOP1					0	//�ⲿֹͣ1
#define	EXT_STOP2					1	//�ⲿֹͣ2
#define	EXT_STOP3					4	//�ⲿֹͣ3
/*�ⲿֹͣ�������Ͷ���*/
#define	EXT_TRIG_FALLING			0	//�½��ش���
#define	EXT_TRIG_RISING				1	//�����ش���

/*PVTģʽ����*/
#define	PVT_MODE1					0	//PVTģʽ1,����ģʽ
#define	PVT_MODE2					1	//PVTģʽ2,ѭ��ģʽ
#define	PVT_MODE3					2	//PVTģʽ3,����FIFOģʽ

/*GPIO����*/
#define GPIO1						0
#define GPIO2						1
#define GPIO3						2
#define GPIO4						3
#define GPIO5						4
#define GPIO6						5
#define GPIO7						6
#define GPIO_EXT1					7
#define GPIO_EXT2					8
#define GPIO_EXT3					9
#define GPIO_ENC1					9
#define GPIO_ENC2					10
#define GPIO8						11
/*GPIO����*/
#define GPIO_DIR_IN					0
#define GPIO_DIR_OUT				1
/*GPIO����˿�����*/
#define GPIO_IN_FLOATING			0
#define GPIO_IN_IPU					1
#define GPIO_IN_IPD					2
#define GPIO_IN_AIN					3
/*GPIO����˿�����*/
#define GPIO_OUT_OD					0
#define GPIO_OUT_PP					1

/*��ɫ����*/
#ifndef RGB
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif

/*RPDOͨ������*/
#define RPDO_CH1					0 //����PDOͨ��1
#define RPDO_CH2					1 //����PDOͨ��2
#define RPDO_CH3					2 //����PDOͨ��3
#define RPDO_CH4					3 //����PDOͨ��4

/*TPDOͨ������*/
#define TPDO_CH1					0 //����PDOͨ��1
#define TPDO_CH2					1 //����PDOͨ��2
#define TPDO_CH3					2 //����PDOͨ��3
#define TPDO_CH4					3 //����PDOͨ��4

/*PP/PVģʽ������λ����*/
//��ֵ��"0"ת����"1"ʱ��ִ����������
#define CW_NEW_TARGET		(1<<4)
//����λ����Ϊ"1"ʱ��������ִ����λ4������������������λ����Ϊ"0"�������������ִ�е���������Ȼ��������¸���������
#define CW_EXEC_IMM			(1<<5) 
//��ֵ��Ϊ"0"ʱ��Ŀ��λ�� (607Ah) �Ǿ���λ�ã���ֵ��Ϊ"1"ʱ��Ŀ��λ���ǻ��ڵ�ǰλ�õ����λ��
#define CW_ABS				(1<<6)
//����λ��ֵ��"1"��Ϊ"0"ʱ���������Ԥ�������б�¼�����Ŀ���ٶȡ�����λ��ֵ��"0"��Ϊ"1"ʱ����������ٲ�ֹͣ�˶���
#define CW_HALT				(1<<8)
//����λ���趨ʱ�����ڵ����׸�Ŀ��λ�ú�ı��ٶȡ������˵���ڵ����׸�Ŀ��ǰ����ִ���ƶ�����Ϊ�����Ӧͣ�ڸ�λ���ϡ�
#define CW_BRAKE_NONE		(1<<9)

/*PP/PVģʽ״̬��λ����*/
//������Ŀ���ѵ����λ������Ϊ"1"��
#define SW_TARGET_ARRIVED	(1<<10)
//��λȷ���յ���Ч����Ŀ��㡣��λ����Controlword�е�λ"New set-point"ͬ���趨�͸�λ��
#define SW_TARGET_ACK		(1<<12)

/**************************************���Ͷ���**************************************/
/*�������ͺ�*/
typedef enum{
	LANMA_A1PLUS = 0,//�������A1+
	LEDIA = 1,//�ֵ�USB-CAN
	YL9100 = 2,//YL9100
	IXXAT = 3,//IXXAT
	GC_USBCAN_I = 4,//���USBCAN-I
	ZLG_USBCAN_I = 5,//������USBCAN-I
	ZLG_USBCAN_E_U = 6,//������USBCAN-E-U
	ZLG_CANET_TCPC = 7,//������CANET-TCP�ͻ���
	CX_CANALYST_II	= 8,//��оCANalyst-II�������õ������
	ZLG_CANCOM_100IE = 9,//������CANCOM-100IE
}ADAPT_TYPE_T;

/*PUSI CAN�豸�ͺ�*/
typedef enum{
	PMC007C3S = 0,
	PMC007C6S = 1,
	PMC007C3SE = 2,
	PMC007C6SE = 3, //�����õ������
}PCAN_TYPE_T;

typedef enum{
	BR_10KBPS = 0,
	BR_20KBPS = 1,
	BR_50KBPS = 2,
	BR_100KBPS = 3,
	BR_125KBPS = 4,  //һ����125��
	BR_250KBPS = 5,
	BR_500KBPS = 6,
	BR_800KBPS = 7,
	BR_1000KBPS = 8,
}BAUDRATE_T;

typedef enum
{
	PCAN_SUCCESS = 0, /*�����ɹ�*/
	PCAN_GENERNAL_ERR = 1, /*ͨ�ô���*/
	PCAN_LOADDRIVER_FAIL = 2, /* װ������ʧ�� */
	PCAN_OPEN_FAIL = 3,  /*��������ʧ��*/
	PCAN_READSDO_FAIL = 4, /*��SDOʧ��*/
	PCAN_READSDO_TIMEOUT = 5, /*��SDO��ʱ*/
	PCAN_WRITESDO_FAIL = 6, /*дSDOʧ��*/
	PCAN_WRITESDO_TIMEOUT = 7, /*дSDO��ʱ*/	
	PCAN_NOIDLE_SDO_CLIENT = 8,/*SDO�ͻ���û�п��õ�ͨ��*/
	PCAN_WRITEPDO_FAIL = 9,/*дPDOʧ��*/
	PCAN_NO_SUPPORT_TCP_CONNECT = 10,/*��֧��TCP����*/
	PCAN_NO_SUPPORT_SP_CONNECT = 11,/*��֧�ִ�������*/
	PCAN_SLAVE_NOT_ONLINE = 12,/*�ڵ㲻����*/
}PCANResult;

// ���庯��ָ��
typedef PCANResult (__stdcall * LPPCAN_SLAVECHANGECB)(DWORD dwNodeID,BOOL bOnline);
typedef PCANResult (__stdcall * LPPCAN_TRACECB)(char* szTrace);
typedef PCANResult (__stdcall * LPPCAN_TPDOCB)(DWORD dwNodeID,DWORD dwTPDOChannel,BYTE* pTPDOData,DWORD dwLen);

class CAxis
{
public:
	CAxis(void); //���캯��
	CAxis(DWORD dwNodeID);
	~CAxis(void);//��������
//��̬��ӿں���
public:
/*********************ͨ�ÿ��ƺ���*********************/
	/*���ûص�����*/
	static PCANResult SetEventCallback(LPPCAN_SLAVECHANGECB funcSlaveChange, LPPCAN_TRACECB funcTraceCallback, LPPCAN_TPDOCB funcTPDOCallback);
	/*��ʼ��*/
	static PCANResult Init(ADAPT_TYPE_T adaptType, PCAN_TYPE_T devType, DWORD dwTraceLevel);
	/*����TCPͨ�Ų���*/
	static PCANResult SetTCPClient(char *szIPAddr,DWORD dwPort);
	/*���ô��ڲ���*/
	static PCANResult SetSerialPort(DWORD dwPort,DWORD dwBaud);
	/*�򿪶˿�*/
	static PCANResult OpenPort(BAUDRATE_T baudrate);
	/*�رն˿�*/
	static PCANResult ClosePort();
	
/*********************NMT�ڵ����*********************/
	/*�ڵ�����״̬*/
	PCANResult IsSlaveOnline(BOOL *pOnline);
	/*�����ڵ�*/
	PCANResult StartNode();
	/*ֹͣ�ڵ�*/
	PCANResult StopNode();
	/*��λ�ڵ�*/
	PCANResult ResetNode();
	/*��λͨ��*/
	PCANResult ResetCommunication();
	/*����Ԥ����״̬*/
	PCANResult EnterPreoperational();
/*********************ϵͳ����*********************/
	/*��������ֵ����*/
	PCANResult SaveObjectDict();
/*********************��������˶�����*********************/
	/*��ȡ���״̬*/
	PCANResult GetMotorStatus(DWORD* pMotorStatus);
	/*��ȡ����״̬*/
	PCANResult GetControlStatus(DWORD* pControlStatus);
	/*��ȡ���ʹ��*/
	PCANResult GetMotorEnable(BOOL *pMotorEnable);
	/*���õ��ʹ��*/
	PCANResult SetMotorEnable(BOOL bMotorEnable);
	/*��ȡ��ֵ����*/
	PCANResult GetPeakCurrent(DWORD *pPeakCurrent);
	/*���÷�ֵ����*/
	PCANResult SetPeakCurrent(DWORD dwPeakCurrent);
	/*��ȡ����˥��*/
	PCANResult GetCurrentDecay(DWORD *pCurrentDecay);
	/*���õ���˥��*/
	PCANResult SetCurrentDecay(DWORD dwCurrentDecay);
	/*��ȡϸ����*/
	PCANResult GetMicroStep(DWORD *pMicroStep);
	/*����ϸ����*/
	PCANResult SetMicroStep(DWORD dwMicroStep);
	/*��ȡ����ģʽ*/
	PCANResult GetWorkMode(DWORD *pWorkMode);
	/*���ù���ģʽ*/
	PCANResult SetWorkMode(DWORD dwWorkMode);
	/*��ȡת������*/
	PCANResult GetDir(DWORD *pDir);
	/*����ת������*/
	PCANResult SetDir(DWORD dir);
	/*��ȡ�����ٶ�*/
	PCANResult GetStartSpeed(DWORD *pStartSpeed);
	/*���������ٶ�*/
	PCANResult SetStartSpeed(DWORD dwStartSpeed);
	/*��ȡֹͣ�ٶ�*/
	PCANResult GetStopSpeed(DWORD *pStopSpeed);
	/*����ֹͣ�ٶ�*/
	PCANResult SetStopSpeed(DWORD dwStopSpeed);
	/*��ȡ���ٶ�ϵ��*/
	PCANResult GetAccel(DWORD *pAccel);
	/*���ü��ٶ�ϵ��*/
	PCANResult SetAccel(DWORD dwAccel);
	/*��ȡ���ٶ�ϵ��*/
	PCANResult GetDecel(DWORD *pDecel);
	/*���ü��ٶ�ϵ��*/
	PCANResult SetDecel(DWORD dwDecel);
	/*��ȡ����ٶ�*/
	PCANResult GetMaxSpeed(int *pMaxSpeed);
	/*��������ٶ�*/
	PCANResult SetMaxSpeed(int nMaxSpeed);
	/*PP/PVģʽ����Ŀ��λ��*/
	PCANResult GetTargetPos(int *pTargetPos);
	/*PP/PVģʽ����Ŀ��λ��*/
	PCANResult SetTargetPos(int nTargetPos);
	/*��ȡ���λ��*/
	PCANResult GetMotorPos(int *pMotorPos);
	/*�������λ��*/
	PCANResult SetMotorPos(int nMotorPos);
	/*���λ�ò���*/
	PCANResult StartRelStep(DWORD dwStepNum);
	/*����λ�ò���*/
	PCANResult StartAbsStep(int nAbsPos);
	/*��ֹ����*/
	PCANResult AbortStep();
/*********************����������*********************/
	/*��ȡ�ⲿ����ֹͣʹ��*/
	PCANResult GetExtStopEnable(DWORD *pExtStopEnable);
	/*�����ⲿ����ֹͣʹ��*/
	PCANResult SetExtStopEnable(DWORD dwExtStopEnable);
	/*��ȡ�ⲿ����ֹͣ������ʽ*/
	PCANResult GetExtStopTrigger(DWORD *pExtStopTrigger);
	/*�����ⲿ����ֹͣ������ʽ*/
	PCANResult SetExtStopTrigger(DWORD dwExtStopTrigger);
	/*��ȡ�ⲿ����ֹͣȥ����ʱ*/
	PCANResult GetDebounceDelay(DWORD *pDebounceDelay);
	/*�����ⲿ����ֹͣȥ����ʱ*/
	PCANResult SetDebounceDelay(DWORD dwDebounceDelay);
	/*����ⲿ����ֹͣ��־*/
	PCANResult ClearExtStopFlag(DWORD dwExtStopFlag);
/*********************PVT�˶�����*********************/
	/*������ID*/
	PCANResult SetGroupID(DWORD dwGroupID);
	/*����PVTģʽ*/
	PCANResult SetPVTMode(DWORD dwPVTMode);
	/*�������PVT���ݸ���*/
	PCANResult SetMaxPVTNum(DWORD dwMaxPVTNum);
	/*����PVT1����*/
	PCANResult SetPVT1Para(DWORD dwStartIndex,DWORD dwEndIndex);
	/*����PVT2����*/
	PCANResult SetPVT2Para(DWORD dwAccStartIndex,DWORD dwAccEndIndex,DWORD dwLoopStartIndex,\
		DWORD dwLoopEndIndex,DWORD dwLoopCount,DWORD dwDecStartIndex,DWORD dwDecEndIndex);
	/*����PVT3����*/
	PCANResult SetPVT3Para(DWORD dwLowThreshold,DWORD dwHighThreshold);	
	/*SDOдPVT����*/
	PCANResult SDOWritePVT(int nPosition, int nVelocity, DWORD dwTime);
	/*����PVT����*/
	static PCANResult StartPVTStep(DWORD dwGroupID);
	/*ֹͣPVT����*/
	static PCANResult StopPVTStep(DWORD dwGroupID);
/*********************PV�˶�����*********************/
	/*дPV����*/
	PCANResult PCAN_SetSyncPosPara(int nPosition,int nVelocity);
	/*����PV����*/
	static PCANResult PCAN_StartSyncStep(DWORD dwGroupID);
/*********************�˿ڿ���*********************/
	/*��ȡGPIO����*/
	PCANResult GetGPIODir(DWORD *pGPIODir);
	/*����GPIO����*/
	PCANResult SetGPIODir(DWORD dwGPIODir);
	/*��ȡGPIO����*/
	PCANResult GetGPIOConfig(DWORD *pGPIOConfig);
	/*����GPIO����*/
	PCANResult SetGPIOConfig(DWORD dwGPIOConfig);
	/*��ȡGPIOֵ*/
	PCANResult GetGPIOValue(DWORD *pGPIOValue);
	/*����GPIOֵ*/
	PCANResult SetGPIOValue(DWORD dwGPIOValue);
/*********************�òʵƿ���*********************/
	/*�òʵƲ���*/
	PCANResult SetColorLedPara(DWORD dwFreq,DWORD dwDutyCycle0,DWORD dwDutyCycle1);
	/*�òʵ�ʹ��*/
	PCANResult SetColorLedEnable(BOOL enable);
	/*�òʵ���ɫ����*/
	PCANResult SetColorLed(DWORD dwColor);
/*********************PDO���ƽӿ�*********************/
	/*дPDO*/
	PCANResult WritePDO(DWORD dwRPDOChannel,BYTE *data,DWORD dwLen);
	/*��PDO*/
	PCANResult ReadPDO(DWORD dwTPDOChannel,BYTE *data,DWORD *pLen);
	/*����״̬*/
	void UpdateControlStatus(BYTE status);
	PCANResult WritePVT(int nPosition,int nVelocity,DWORD dwTime);
private:
	static HMODULE m_hModule; //��̬��ģ����
	static DWORD m_dwInstanceCount; //���ʵ������
	static LPPCAN_SLAVECHANGECB m_pfnSlaveChangeCallback; //��վ״̬�ı�ص�����
	static LPPCAN_TRACECB m_pfnTraceCallback; //��վ�ĸ�����Ϣ
	static LPPCAN_TPDOCB m_pfnTPDOCallback; //��վ��TPDO�ص���Ϣ
	BYTE m_szTPDOData[4][8]; //TPDO ͨ������
	BYTE m_szRPDOData[4][8]; //RPDO ͨ������
public:
	DWORD m_dwNodeID;  //�ڵ�ID
	DWORD m_dwGroupID; //��ID
	BOOL m_bSlaveOnline; //��վ����״̬��
	BOOL m_bBusy; //æ״̬
	BOOL m_bPVT3Low; //PVT3 FIFO����
	BOOL m_bPVT3High; //PVT3 FIFO����
	BOOL m_bPVT3Empty; //PVT3 FIFO��
	HANDLE m_hSlaveOnline; //��վ�����¼�
	HANDLE m_hSlaveIdle; //��վ����״̬

};

