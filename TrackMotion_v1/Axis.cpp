#include "stdafx.h"
#include "Axis.h"

HMODULE CAxis::m_hModule = NULL;
DWORD CAxis::m_dwInstanceCount = 0;

LPPCAN_SLAVECHANGECB CAxis::m_pfnSlaveChangeCallback = NULL; //从站状态改变回调函数
LPPCAN_TRACECB CAxis::m_pfnTraceCallback = NULL; //从站的跟踪信息
LPPCAN_TPDOCB CAxis::m_pfnTPDOCallback = NULL; //从站的TPDO回调信息

CAxis::CAxis(void)
{
	CAxis(0);
	m_dwGroupID = 0;
	m_bBusy = FALSE; //忙状态
	m_bPVT3Low = TRUE; //PVT3 FIFO下限
	m_bPVT3High = FALSE; //PVT3 FIFO上限
	m_bPVT3Empty = TRUE;
}

CAxis::CAxis(DWORD dwNodeID)
{
	if(m_hModule == NULL){
		m_hModule = LoadLibrary(L"PUSICANControl.dll");
		if(m_hModule == NULL){
			DWORD a=GetLastError();
			printf("load PUSICANControl.dll FAIL!\nLast error=%d",a);
			getchar();
		}
	}
	m_dwInstanceCount++;
	m_dwNodeID = dwNodeID;
	m_dwGroupID = 0;
	m_bSlaveOnline = FALSE;
	m_hSlaveOnline = CreateEvent(NULL,TRUE,FALSE,NULL);  //自动复位事件状态，初始状态未触发
	m_hSlaveIdle = CreateEvent(NULL,TRUE,TRUE,NULL);  //自动复位事件状态，初始状态未触发
	m_bBusy = FALSE; //忙状态
	m_bPVT3Low = TRUE; //PVT3 FIFO下限
	m_bPVT3High = FALSE; //PVT3 FIFO上限
	m_bPVT3Empty = TRUE;
}

CAxis::~CAxis(void)
{
	m_dwInstanceCount--;
	if(m_dwInstanceCount == 0){
		if(m_hModule != NULL){
			FreeLibrary(m_hModule);
			m_hModule = NULL;
		}
	}
}

PCANResult CAxis::SetEventCallback(LPPCAN_SLAVECHANGECB funcSlaveChange, LPPCAN_TRACECB funcTraceCallback, LPPCAN_TPDOCB funcTPDOCallback)
{
	typedef PCANResult (__stdcall * LPPCAN_SetEventCallback)(LPPCAN_SLAVECHANGECB, LPPCAN_TRACECB, LPPCAN_TPDOCB);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetEventCallback PCAN_SetEventCallback = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetEventCallback = (LPPCAN_SetEventCallback)GetProcAddress(m_hModule,"PCAN_SetEventCallback");
		if(NULL != PCAN_SetEventCallback){
			result = PCAN_SetEventCallback(funcSlaveChange,funcTraceCallback,funcTPDOCallback);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}


PCANResult CAxis::Init(ADAPT_TYPE_T adaptType, PCAN_TYPE_T devType, DWORD dwTraceLevel)
{
	typedef PCANResult (__stdcall * LPPCAN_Init)(ADAPT_TYPE_T, PCAN_TYPE_T, DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_Init PCAN_Init = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_Init = (LPPCAN_Init)GetProcAddress(m_hModule,"PCAN_Init");
		if(NULL != PCAN_Init){
			result = PCAN_Init(adaptType,devType,dwTraceLevel);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetTCPClient(char *szIPAddr,DWORD dwPort)
{
	typedef PCANResult (__stdcall * LPPCAN_SetTCPClient)(char *,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetTCPClient PCAN_SetTCPClient = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetTCPClient = (LPPCAN_SetTCPClient)GetProcAddress(m_hModule,"PCAN_SetTCPClient");
		if(NULL != PCAN_SetTCPClient){
			result = PCAN_SetTCPClient(szIPAddr,dwPort);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetSerialPort(DWORD dwPort,DWORD dwBaud)
{
	typedef PCANResult (__stdcall * LPPCAN_SetSerialPort)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetSerialPort PCAN_SetSerialPort = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetSerialPort = (LPPCAN_SetSerialPort)GetProcAddress(m_hModule,"PCAN_SetSerialPort");
		if(NULL != PCAN_SetSerialPort){
			result = PCAN_SetSerialPort(dwPort,dwBaud);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::OpenPort(BAUDRATE_T baudrate)
{
	typedef PCANResult (__stdcall * LPPCAN_OpenPort)(BAUDRATE_T);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_OpenPort PCAN_OpenPort = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_OpenPort = (LPPCAN_OpenPort)GetProcAddress(m_hModule,"PCAN_OpenPort");
		if(NULL != PCAN_OpenPort){
			result = PCAN_OpenPort(baudrate);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::ClosePort()
{
	typedef PCANResult (__stdcall * LPPCAN_ClosePort)(void);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_ClosePort PCAN_ClosePort = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_ClosePort = (LPPCAN_ClosePort)GetProcAddress(m_hModule,"PCAN_ClosePort");
		if(NULL != PCAN_ClosePort){
			result = PCAN_ClosePort();
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::IsSlaveOnline(BOOL *pOnline)
{
	typedef PCANResult (__stdcall * LPPCAN_IsSlaveOnline)(DWORD,BOOL*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_IsSlaveOnline PCAN_IsSlaveOnline = NULL;
	if(FALSE == m_bSlaveOnline){
		printf("slave is not online!\n");
		return PCAN_SLAVE_NOT_ONLINE;
	}
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_IsSlaveOnline = (LPPCAN_IsSlaveOnline)GetProcAddress(m_hModule,"PCAN_IsSlaveOnline");
		if(NULL != PCAN_IsSlaveOnline){
			result = PCAN_IsSlaveOnline(m_dwNodeID,pOnline);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::StartNode()
{
	typedef PCANResult (__stdcall * LPPCAN_StartNode)(DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_StartNode PCAN_StartNode = NULL;
	if(FALSE == m_bSlaveOnline){
		printf("slave is not online!\n");
		return PCAN_SLAVE_NOT_ONLINE;
	}
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_StartNode = (LPPCAN_StartNode)GetProcAddress(m_hModule,"PCAN_StartNode");
		if(NULL != PCAN_StartNode){
			result = PCAN_StartNode(m_dwNodeID);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::StopNode()
{
	typedef PCANResult (__stdcall * LPPCAN_StopNode)(DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_StopNode PCAN_StopNode = NULL;
	if(FALSE == m_bSlaveOnline){
		printf("slave is not online!\n");
		return PCAN_SLAVE_NOT_ONLINE;
	}
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_StopNode = (LPPCAN_StopNode)GetProcAddress(m_hModule,"PCAN_StopNode");
		if(NULL != PCAN_StopNode){
			result = PCAN_StopNode(m_dwNodeID);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}


PCANResult CAxis::ResetNode()
{
	typedef PCANResult (__stdcall * LPPCAN_ResetNode)(DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_ResetNode PCAN_ResetNode = NULL;
	if(FALSE == m_bSlaveOnline){
		printf("slave is not online!\n");
		return PCAN_SLAVE_NOT_ONLINE;
	}
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_ResetNode = (LPPCAN_ResetNode)GetProcAddress(m_hModule,"PCAN_ResetNode");
		if(NULL != PCAN_ResetNode){
			result = PCAN_ResetNode(m_dwNodeID);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::ResetCommunication()
{
	typedef PCANResult (__stdcall * LPPCAN_ResetCommunication)(DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_ResetCommunication PCAN_ResetCommunication = NULL;
	if(FALSE == m_bSlaveOnline){
		printf("slave is not online!\n");
		return PCAN_SLAVE_NOT_ONLINE;
	}
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_ResetCommunication = (LPPCAN_ResetCommunication)GetProcAddress(m_hModule,"PCAN_ResetCommunication");
		if(NULL != PCAN_ResetCommunication){
			result = PCAN_ResetCommunication(m_dwNodeID);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::EnterPreoperational()
{
	typedef PCANResult (__stdcall * LPPCAN_EnterPreoperational)(DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_EnterPreoperational PCAN_EnterPreoperational = NULL;
	if(FALSE == m_bSlaveOnline){
		printf("slave is not online!\n");
		return PCAN_SLAVE_NOT_ONLINE;
	}
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_EnterPreoperational = (LPPCAN_EnterPreoperational)GetProcAddress(m_hModule,"PCAN_EnterPreoperational");
		if(NULL != PCAN_EnterPreoperational){
			result = PCAN_EnterPreoperational(m_dwNodeID);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SaveObjectDict()
{
	typedef PCANResult (__stdcall * LPPCAN_SaveObjectDict)(DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SaveObjectDict PCAN_SaveObjectDict = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SaveObjectDict = (LPPCAN_SaveObjectDict)GetProcAddress(m_hModule,"PCAN_SaveObjectDict");
		if(NULL != PCAN_SaveObjectDict){
			result = PCAN_SaveObjectDict(m_dwNodeID);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetMotorStatus(DWORD* pMotorStatus)
{
	typedef PCANResult (__stdcall * LPPCAN_GetMotorStatus)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetMotorStatus PCAN_GetMotorStatus = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetMotorStatus = (LPPCAN_GetMotorStatus)GetProcAddress(m_hModule,"PCAN_GetMotorStatus");
		if(NULL != PCAN_GetMotorStatus){
			result = PCAN_GetMotorStatus(m_dwNodeID,pMotorStatus);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetControlStatus(DWORD* pControlStatus)
{
	typedef PCANResult (__stdcall * LPPCAN_GetControlStatus)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetControlStatus PCAN_GetControlStatus = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetControlStatus = (LPPCAN_GetControlStatus)GetProcAddress(m_hModule,"PCAN_GetControlStatus");
		if(NULL != PCAN_GetControlStatus){
			result = PCAN_GetControlStatus(m_dwNodeID,pControlStatus);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetMotorEnable(BOOL *pMotorEnable)
{
	typedef PCANResult (__stdcall * LPPCAN_GetMotorEnable)(DWORD,BOOL*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetMotorEnable PCAN_GetMotorEnable = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetMotorEnable = (LPPCAN_GetMotorEnable)GetProcAddress(m_hModule,"PCAN_GetMotorEnable");
		if(NULL != PCAN_GetMotorEnable){
			result = PCAN_GetMotorEnable(m_dwNodeID,pMotorEnable);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}


PCANResult CAxis::SetMotorEnable(BOOL bMotorEnable)
{
	typedef PCANResult (__stdcall * LPPCAN_SetMotorEnable)(DWORD,BOOL);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetMotorEnable PCAN_SetMotorEnable = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetMotorEnable = (LPPCAN_SetMotorEnable)GetProcAddress(m_hModule,"PCAN_SetMotorEnable");
		if(NULL != PCAN_SetMotorEnable){
			result = PCAN_SetMotorEnable(m_dwNodeID,bMotorEnable);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetPeakCurrent(DWORD *pPeakCurrent)
{
	typedef PCANResult (__stdcall * LPPCAN_GetPeakCurrent)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetPeakCurrent PCAN_GetPeakCurrent = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetPeakCurrent = (LPPCAN_GetPeakCurrent)GetProcAddress(m_hModule,"PCAN_GetPeakCurrent");
		if(NULL != PCAN_GetPeakCurrent){
			result = PCAN_GetPeakCurrent(m_dwNodeID,pPeakCurrent);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetPeakCurrent(DWORD dwPeakCurrent)
{
	typedef PCANResult (__stdcall * LPPCAN_SetPeakCurrent)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetPeakCurrent PCAN_SetPeakCurrent = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetPeakCurrent = (LPPCAN_SetPeakCurrent)GetProcAddress(m_hModule,"PCAN_SetPeakCurrent");
		if(NULL != PCAN_SetPeakCurrent){
			result = PCAN_SetPeakCurrent(m_dwNodeID,dwPeakCurrent);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetCurrentDecay(DWORD *pCurrentDecay)
{
	typedef PCANResult (__stdcall * LPPCAN_GetCurrentDecay)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetCurrentDecay PCAN_GetCurrentDecay = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetCurrentDecay = (LPPCAN_GetCurrentDecay)GetProcAddress(m_hModule,"PCAN_GetCurrentDecay");
		if(NULL != PCAN_GetCurrentDecay){
			result = PCAN_GetCurrentDecay(m_dwNodeID,pCurrentDecay);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetCurrentDecay(DWORD dwCurrentDecay)
{
	typedef PCANResult (__stdcall * LPPCAN_SetCurrentDecay)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetCurrentDecay PCAN_SetCurrentDecay = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetCurrentDecay = (LPPCAN_SetCurrentDecay)GetProcAddress(m_hModule,"PCAN_SetCurrentDecay");
		if(NULL != PCAN_SetCurrentDecay){
			result = PCAN_SetCurrentDecay(m_dwNodeID,dwCurrentDecay);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetMicroStep(DWORD *pMicroStep)
{
	typedef PCANResult (__stdcall * LPPCAN_GetMicroStep)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetMicroStep PCAN_GetMicroStep = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetMicroStep = (LPPCAN_GetMicroStep)GetProcAddress(m_hModule,"PCAN_GetMicroStep");
		if(NULL != PCAN_GetMicroStep){
			result = PCAN_GetMicroStep(m_dwNodeID,pMicroStep);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}


PCANResult CAxis::SetMicroStep(DWORD dwMicroStep)
{
	typedef PCANResult (__stdcall * LPPCAN_SetMicroStep)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetMicroStep PCAN_SetMicroStep = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetMicroStep = (LPPCAN_SetMicroStep)GetProcAddress(m_hModule,"PCAN_SetMicroStep");
		if(NULL != PCAN_SetMicroStep){
			result = PCAN_SetMicroStep(m_dwNodeID,dwMicroStep);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetWorkMode(DWORD *pWorkMode)
{
	typedef PCANResult (__stdcall * LPPCAN_GetWorkMode)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetWorkMode PCAN_GetWorkMode = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetWorkMode = (LPPCAN_GetWorkMode)GetProcAddress(m_hModule,"PCAN_GetWorkMode");
		if(NULL != PCAN_GetWorkMode){
			result = PCAN_GetWorkMode(m_dwNodeID,pWorkMode);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetWorkMode(DWORD dwWorkMode)
{
	typedef PCANResult (__stdcall * LPPCAN_SetWorkMode)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetWorkMode PCAN_SetWorkMode = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetWorkMode = (LPPCAN_SetWorkMode)GetProcAddress(m_hModule,"PCAN_SetWorkMode");
		if(NULL != PCAN_SetWorkMode){
			result = PCAN_SetWorkMode(m_dwNodeID,dwWorkMode);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetDir(DWORD *pDir)
{
	typedef PCANResult (__stdcall * LPPCAN_GetDir)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetDir PCAN_GetDir = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetDir = (LPPCAN_GetDir)GetProcAddress(m_hModule,"PCAN_SetWorkMode");
		if(NULL != PCAN_GetDir){
			result = PCAN_GetDir(m_dwNodeID,pDir);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetDir(DWORD dir)
{
	typedef PCANResult (__stdcall * LPPCAN_SetDir)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetDir PCAN_SetDir = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetDir = (LPPCAN_SetDir)GetProcAddress(m_hModule,"PCAN_SetWorkMode");
		if(NULL != PCAN_SetDir){
			result = PCAN_SetDir(m_dwNodeID,dir);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetStartSpeed(DWORD *pStartSpeed)
{
	typedef PCANResult (__stdcall * LPPCAN_GetStartSpeed)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetStartSpeed PCAN_GetStartSpeed = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetStartSpeed = (LPPCAN_GetStartSpeed)GetProcAddress(m_hModule,"PCAN_GetStartSpeed");
		if(NULL != PCAN_GetStartSpeed){
			result = PCAN_GetStartSpeed(m_dwNodeID,pStartSpeed);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetStartSpeed(DWORD dwStartSpeed)
{
	typedef PCANResult (__stdcall * LPPCAN_SetStartSpeed)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetStartSpeed PCAN_SetStartSpeed = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetStartSpeed = (LPPCAN_SetStartSpeed)GetProcAddress(m_hModule,"PCAN_SetStartSpeed");
		if(NULL != PCAN_SetStartSpeed){
			result = PCAN_SetStartSpeed(m_dwNodeID,dwStartSpeed);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetStopSpeed(DWORD *pStopSpeed)
{
	typedef PCANResult (__stdcall * LPPCAN_GetStopSpeed)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetStopSpeed PCAN_GetStopSpeed = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetStopSpeed = (LPPCAN_GetStopSpeed)GetProcAddress(m_hModule,"PCAN_GetStopSpeed");
		if(NULL != PCAN_GetStopSpeed){
			result = PCAN_GetStopSpeed(m_dwNodeID,pStopSpeed);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetStopSpeed(DWORD dwStopSpeed)
{
	typedef PCANResult (__stdcall * LPPCAN_SetStopSpeed)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetStopSpeed PCAN_SetStopSpeed = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetStopSpeed = (LPPCAN_SetStopSpeed)GetProcAddress(m_hModule,"PCAN_SetStopSpeed");
		if(NULL != PCAN_SetStopSpeed){
			result = PCAN_SetStopSpeed(m_dwNodeID,dwStopSpeed);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetAccel(DWORD *pAccel)
{
	typedef PCANResult (__stdcall * LPPCAN_GetAccel)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetAccel PCAN_GetAccel = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetAccel = (LPPCAN_GetAccel)GetProcAddress(m_hModule,"PCAN_GetAccel");
		if(NULL != PCAN_GetAccel){
			result = PCAN_GetAccel(m_dwNodeID,pAccel);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetAccel(DWORD dwAccel)
{
	typedef PCANResult (__stdcall * LPPCAN_SetAccel)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetAccel PCAN_SetAccel = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetAccel = (LPPCAN_SetAccel)GetProcAddress(m_hModule,"PCAN_SetAccel");
		if(NULL != PCAN_SetAccel){
			result = PCAN_SetAccel(m_dwNodeID,dwAccel);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetDecel(DWORD *pDecel)
{
	typedef PCANResult (__stdcall * LPPCAN_GetDecel)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetDecel PCAN_GetDecel = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetDecel = (LPPCAN_GetDecel)GetProcAddress(m_hModule,"PCAN_GetDecel");
		if(NULL != PCAN_GetDecel){
			result = PCAN_GetDecel(m_dwNodeID,pDecel);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetDecel(DWORD dwDecel)
{
	typedef PCANResult (__stdcall * LPPCAN_SetDecel)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetDecel PCAN_SetDecel = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetDecel = (LPPCAN_SetDecel)GetProcAddress(m_hModule,"PCAN_SetDecel");
		if(NULL != PCAN_SetDecel){
			result = PCAN_SetDecel(m_dwNodeID,dwDecel);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetMaxSpeed(int *pMaxSpeed)
{
	typedef PCANResult (__stdcall * LPPCAN_GetMaxSpeed)(DWORD,int*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetMaxSpeed PCAN_GetMaxSpeed = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetMaxSpeed = (LPPCAN_GetMaxSpeed)GetProcAddress(m_hModule,"PCAN_GetMaxSpeed");
		if(NULL != PCAN_GetMaxSpeed){
			result = PCAN_GetMaxSpeed(m_dwNodeID,pMaxSpeed);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetMaxSpeed(int nMaxSpeed)
{
	typedef PCANResult (__stdcall * LPPCAN_SetMaxSpeed)(DWORD,int);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetMaxSpeed PCAN_SetMaxSpeed = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetMaxSpeed = (LPPCAN_SetMaxSpeed)GetProcAddress(m_hModule,"PCAN_SetMaxSpeed");
		if(NULL != PCAN_SetMaxSpeed){
			result = PCAN_SetMaxSpeed(m_dwNodeID,nMaxSpeed);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetTargetPos(int *pTargetPos)
{
	typedef PCANResult (__stdcall * LPPCAN_GetTargetPos)(DWORD,int*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetTargetPos PCAN_GetTargetPos = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetTargetPos = (LPPCAN_GetTargetPos)GetProcAddress(m_hModule,"PCAN_GetTargetPos");
		if(NULL != PCAN_GetTargetPos){
			result = PCAN_GetTargetPos(m_dwNodeID,pTargetPos);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetTargetPos(int nTargetPos)
{
	typedef PCANResult (__stdcall * LPPCAN_SetTargetPos)(DWORD,int);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetTargetPos PCAN_SetTargetPos = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetTargetPos = (LPPCAN_SetTargetPos)GetProcAddress(m_hModule,"PCAN_SetTargetPos");
		if(NULL != PCAN_SetTargetPos){
			result = PCAN_SetTargetPos(m_dwNodeID,nTargetPos);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetMotorPos(int *pMotorPos)
{
	typedef PCANResult (__stdcall * LPPCAN_GetMotorPos)(DWORD,int*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetMotorPos PCAN_GetMotorPos = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetMotorPos = (LPPCAN_GetMotorPos)GetProcAddress(m_hModule,"PCAN_GetMotorPos");
		if(NULL != PCAN_GetMotorPos){
			result = PCAN_GetMotorPos(m_dwNodeID,pMotorPos);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetMotorPos(int nMotorPos)
{
	typedef PCANResult (__stdcall * LPPCAN_SetMotorPos)(DWORD,int);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetMotorPos PCAN_SetMotorPos = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetMotorPos = (LPPCAN_SetMotorPos)GetProcAddress(m_hModule,"PCAN_SetMotorPos");
		if(NULL != PCAN_SetMotorPos){
			result = PCAN_SetMotorPos(m_dwNodeID,nMotorPos);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::StartRelStep(DWORD dwStepNum)
{
	typedef PCANResult (__stdcall * LPPCAN_StartRelStep)(DWORD,int);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_StartRelStep PCAN_StartRelStep = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_StartRelStep = (LPPCAN_StartRelStep)GetProcAddress(m_hModule,"PCAN_StartRelStep");
		if(NULL != PCAN_StartRelStep){
			result = PCAN_StartRelStep(m_dwNodeID,dwStepNum);
			if(PCAN_SUCCESS == result){
				::ResetEvent(m_hSlaveIdle);
			}
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::StartAbsStep(int nAbsPos)
{
	typedef PCANResult (__stdcall * LPPCAN_StartAbsStep)(DWORD,int);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_StartAbsStep PCAN_StartAbsStep = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_StartAbsStep = (LPPCAN_StartAbsStep)GetProcAddress(m_hModule,"PCAN_StartAbsStep");
		if(NULL != PCAN_StartAbsStep){
			result = PCAN_StartAbsStep(m_dwNodeID,nAbsPos);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::AbortStep()
{
	typedef PCANResult (__stdcall * LPPCAN_AbortStep)(DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_AbortStep PCAN_AbortStep = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_AbortStep = (LPPCAN_AbortStep)GetProcAddress(m_hModule,"PCAN_AbortStep");
		if(NULL != PCAN_AbortStep){
			result = PCAN_AbortStep(m_dwNodeID);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetExtStopEnable(DWORD *pExtStopEnable)
{
	typedef PCANResult (__stdcall * LPPCAN_GetExtStopEnable)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetExtStopEnable PCAN_GetExtStopEnable = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetExtStopEnable = (LPPCAN_GetExtStopEnable)GetProcAddress(m_hModule,"PCAN_GetExtStopEnable");
		if(NULL != PCAN_GetExtStopEnable){
			result = PCAN_GetExtStopEnable(m_dwNodeID,pExtStopEnable);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetExtStopEnable(DWORD dwExtStopEnable)
{
	typedef PCANResult (__stdcall * LPPCAN_SetExtStopEnable)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetExtStopEnable PCAN_SetExtStopEnable = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetExtStopEnable = (LPPCAN_SetExtStopEnable)GetProcAddress(m_hModule,"PCAN_SetExtStopEnable");
		if(NULL != PCAN_SetExtStopEnable){
			result = PCAN_SetExtStopEnable(m_dwNodeID,dwExtStopEnable);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetExtStopTrigger(DWORD *pExtStopTrigger)
{
	typedef PCANResult (__stdcall * LPPCAN_GetExtStopTrigger)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetExtStopTrigger PCAN_GetExtStopTrigger = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetExtStopTrigger = (LPPCAN_GetExtStopTrigger)GetProcAddress(m_hModule,"PCAN_GetExtStopTrigger");
		if(NULL != PCAN_GetExtStopTrigger){
			result = PCAN_GetExtStopTrigger(m_dwNodeID,pExtStopTrigger);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetExtStopTrigger(DWORD dwExtStopTrigger)
{
	typedef PCANResult (__stdcall * LPPCAN_SetExtStopTrigger)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetExtStopTrigger PCAN_SetExtStopTrigger = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetExtStopTrigger = (LPPCAN_SetExtStopTrigger)GetProcAddress(m_hModule,"PCAN_SetExtStopTrigger");
		if(NULL != PCAN_SetExtStopTrigger){
			result = PCAN_SetExtStopTrigger(m_dwNodeID,dwExtStopTrigger);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetDebounceDelay(DWORD *pDebounceDelay)
{
	typedef PCANResult (__stdcall * LPPCAN_GetDebounceDelay)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetDebounceDelay PCAN_GetDebounceDelay = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetDebounceDelay = (LPPCAN_GetDebounceDelay)GetProcAddress(m_hModule,"PCAN_GetDebounceDelay");
		if(NULL != PCAN_GetDebounceDelay){
			result = PCAN_GetDebounceDelay(m_dwNodeID,pDebounceDelay);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetDebounceDelay(DWORD dwDebounceDelay)
{
	typedef PCANResult (__stdcall * LPPCAN_SetDebounceDelay)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetDebounceDelay PCAN_SetDebounceDelay = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetDebounceDelay = (LPPCAN_SetDebounceDelay)GetProcAddress(m_hModule,"PCAN_GetDebounceDelay");
		if(NULL != PCAN_SetDebounceDelay){
			result = PCAN_SetDebounceDelay(m_dwNodeID,dwDebounceDelay);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::ClearExtStopFlag(DWORD dwExtStopFlag)
{
	typedef PCANResult (__stdcall * LPPCAN_ClearExtStopFlag)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_ClearExtStopFlag PCAN_ClearExtStopFlag = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_ClearExtStopFlag = (LPPCAN_ClearExtStopFlag)GetProcAddress(m_hModule,"PCAN_ClearExtStopFlag");
		if(NULL != PCAN_ClearExtStopFlag){
			result = PCAN_ClearExtStopFlag(m_dwNodeID,dwExtStopFlag);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetGroupID(DWORD dwGroupID)
{
	typedef PCANResult (__stdcall * LPPCAN_SetGroupID)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetGroupID PCAN_SetGroupID = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetGroupID = (LPPCAN_SetGroupID)GetProcAddress(m_hModule,"PCAN_SetGroupID");
		if(NULL != PCAN_SetGroupID){
			result = PCAN_SetGroupID(m_dwNodeID,dwGroupID);
			m_dwGroupID = dwGroupID;
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetPVTMode(DWORD dwPVTMode)
{
	typedef PCANResult (__stdcall * LPPCAN_SetPVTMode)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetPVTMode PCAN_SetPVTMode = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetPVTMode = (LPPCAN_SetPVTMode)GetProcAddress(m_hModule,"PCAN_SetPVTMode");
		if(NULL != PCAN_SetPVTMode){
			result = PCAN_SetPVTMode(m_dwNodeID,dwPVTMode);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetMaxPVTNum(DWORD dwMaxPVTNum)
{
	typedef PCANResult (__stdcall * LPPCAN_SetMaxPVTNum)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetMaxPVTNum PCAN_SetMaxPVTNum = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetMaxPVTNum = (LPPCAN_SetMaxPVTNum)GetProcAddress(m_hModule,"PCAN_SetMaxPVTNum");
		if(NULL != PCAN_SetMaxPVTNum){
			result = PCAN_SetMaxPVTNum(m_dwNodeID,dwMaxPVTNum);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetPVT1Para(DWORD dwStartIndex,DWORD dwEndIndex)
{
	typedef PCANResult (__stdcall * LPPCAN_SetPVT1Para)(DWORD,DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetPVT1Para PCAN_SetPVT1Para = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetPVT1Para = (LPPCAN_SetPVT1Para)GetProcAddress(m_hModule,"PCAN_SetPVT1Para");
		if(NULL != PCAN_SetPVT1Para){
			result = PCAN_SetPVT1Para(m_dwNodeID,dwStartIndex,dwEndIndex);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetPVT2Para(DWORD dwAccStartIndex,DWORD dwAccEndIndex,DWORD dwLoopStartIndex,\
							  DWORD dwLoopEndIndex,DWORD dwLoopCount,DWORD dwDecStartIndex,DWORD dwDecEndIndex)
{
	typedef PCANResult (__stdcall * LPPCAN_SetPVT2Para)(DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetPVT2Para PCAN_SetPVT2Para = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetPVT2Para = (LPPCAN_SetPVT2Para)GetProcAddress(m_hModule,"PCAN_SetPVT2Para");
		if(NULL != PCAN_SetPVT2Para){
			result = PCAN_SetPVT2Para(m_dwNodeID,dwAccStartIndex,dwAccEndIndex,dwLoopStartIndex,dwLoopEndIndex,\
				dwLoopCount,dwDecStartIndex,dwDecEndIndex);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetPVT3Para(DWORD dwLowThreshold,DWORD dwHighThreshold)
{
	typedef PCANResult (__stdcall * LPPCAN_SetPVT3Para)(DWORD,DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetPVT3Para PCAN_SetPVT3Para = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetPVT3Para = (LPPCAN_SetPVT3Para)GetProcAddress(m_hModule,"PCAN_SetPVT3Para");
		if(NULL != PCAN_SetPVT3Para){
			result = PCAN_SetPVT3Para(m_dwNodeID,dwLowThreshold,dwHighThreshold);	
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SDOWritePVT(int nPosition,int nVelocity,DWORD dwTime)
{
	typedef PCANResult (__stdcall * LPPCAN_WritePVT)(DWORD,int,int,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_WritePVT PCAN_WritePVT = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_WritePVT = (LPPCAN_WritePVT)GetProcAddress(m_hModule,"PCAN_WritePVT");
		if(NULL != PCAN_WritePVT){
			result = PCAN_WritePVT(m_dwNodeID,nPosition,nVelocity,dwTime);		
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}


PCANResult CAxis::StartPVTStep(DWORD dwGroupID)
{
	typedef PCANResult (__stdcall * LPPCAN_StartPVTStep)(DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_StartPVTStep PCAN_StartPVTStep = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_StartPVTStep = (LPPCAN_StartPVTStep)GetProcAddress(m_hModule,"PCAN_StartPVTStep");
		if(NULL != PCAN_StartPVTStep){
			result = PCAN_StartPVTStep(dwGroupID);		
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::StopPVTStep(DWORD dwGroupID)
{
	typedef PCANResult (__stdcall * LPPCAN_StopPVTStep)(DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_StopPVTStep PCAN_StopPVTStep = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_StopPVTStep = (LPPCAN_StopPVTStep)GetProcAddress(m_hModule,"PCAN_StopPVTStep");
		if(NULL != PCAN_StopPVTStep){
			result = PCAN_StopPVTStep(dwGroupID);		
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}
/*
PCANResult CAxis::WritePV(int nPosition,int nVelocity)
{
typedef PCANResult (__stdcall * LPPCAN_WritePV)(DWORD,int,int);
PCANResult result = PCAN_SUCCESS;
LPPCAN_WritePV PCAN_WritePV = NULL;
if(m_hModule != NULL){
//获取动态连接库里的函数地址。
PCAN_WritePV = (LPPCAN_WritePV)GetProcAddress(m_hModule,"PCAN_WritePV");
if(NULL != PCAN_WritePV){
result = PCAN_WritePV(m_dwNodeID,nPosition,nVelocity);
}
}else{
result = PCAN_LOADDRIVER_FAIL;
}
return result;
}

PCANResult CAxis::StartPVStep(DWORD dwGroupID)
{
typedef PCANResult (__stdcall * LPPCAN_StartPVStep)(DWORD);
PCANResult result = PCAN_SUCCESS;
LPPCAN_StartPVStep PCAN_StartPVStep = NULL;
if(m_hModule != NULL){
//获取动态连接库里的函数地址。
PCAN_StartPVStep = (LPPCAN_StartPVStep)GetProcAddress(m_hModule,"PCAN_StartPVStep");
if(NULL != PCAN_StartPVStep){
result = PCAN_StartPVStep(dwGroupID);		
}
}else{
result = PCAN_LOADDRIVER_FAIL;
}
return result;
}
*/
PCANResult CAxis::GetGPIODir(DWORD *pGPIODir)
{
	typedef PCANResult (__stdcall * LPPCAN_GetGPIODir)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetGPIODir PCAN_GetGPIODir = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetGPIODir = (LPPCAN_GetGPIODir)GetProcAddress(m_hModule,"PCAN_GetGPIODir");
		if(NULL != PCAN_GetGPIODir){
			result = PCAN_GetGPIODir(m_dwNodeID,pGPIODir);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetGPIODir(DWORD dwGPIODir)
{
	typedef PCANResult (__stdcall * LPPCAN_SetGPIODir)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetGPIODir PCAN_SetGPIODir = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetGPIODir = (LPPCAN_SetGPIODir)GetProcAddress(m_hModule,"PCAN_SetGPIODir");
		if(NULL != PCAN_SetGPIODir){
			result = PCAN_SetGPIODir(m_dwNodeID,dwGPIODir);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}


PCANResult CAxis::GetGPIOConfig(DWORD *pGPIOConfig)
{
	typedef PCANResult (__stdcall * LPPCAN_GetGPIOConfig)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetGPIOConfig PCAN_GetGPIOConfig = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetGPIOConfig = (LPPCAN_GetGPIOConfig)GetProcAddress(m_hModule,"PCAN_GetGPIOConfig");
		if(NULL != PCAN_GetGPIOConfig){
			result = PCAN_GetGPIOConfig(m_dwNodeID,pGPIOConfig);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetGPIOConfig(DWORD dwGPIOConfig)
{
	typedef PCANResult (__stdcall * LPPCAN_SetGPIOConfig)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetGPIOConfig PCAN_SetGPIOConfig = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetGPIOConfig = (LPPCAN_SetGPIOConfig)GetProcAddress(m_hModule,"PCAN_SetGPIOConfig");
		if(NULL != PCAN_SetGPIOConfig){
			result = PCAN_SetGPIOConfig(m_dwNodeID,dwGPIOConfig);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::GetGPIOValue(DWORD *pGPIOValue)
{
	typedef PCANResult (__stdcall * LPPCAN_GetGPIOValue)(DWORD,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_GetGPIOValue PCAN_GetGPIOValue = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_GetGPIOValue = (LPPCAN_GetGPIOValue)GetProcAddress(m_hModule,"PCAN_GetGPIOValue");
		if(NULL != PCAN_GetGPIOValue){
			result = PCAN_GetGPIOValue(m_dwNodeID,pGPIOValue);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetGPIOValue(DWORD dwGPIOValue)
{
	typedef PCANResult (__stdcall * LPPCAN_SetGPIOValue)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetGPIOValue PCAN_SetGPIOValue = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetGPIOValue = (LPPCAN_SetGPIOValue)GetProcAddress(m_hModule,"PCAN_SetGPIOValue");
		if(NULL != PCAN_SetGPIOValue){
			result = PCAN_SetGPIOValue(m_dwNodeID,dwGPIOValue);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetColorLedPara(DWORD dwFreq,DWORD dwDutyCycle0,DWORD dwDutyCycle1)
{
	typedef PCANResult (__stdcall * LPPCAN_SetColorLedPara)(DWORD,DWORD,DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetColorLedPara PCAN_SetColorLedPara = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetColorLedPara = (LPPCAN_SetColorLedPara)GetProcAddress(m_hModule,"PCAN_SetColorLedPara");
		if(NULL != PCAN_SetColorLedPara){
			result = PCAN_SetColorLedPara(m_dwNodeID,dwFreq,dwDutyCycle0,dwDutyCycle1);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetColorLedEnable(BOOL enable)
{
	typedef PCANResult (__stdcall * LPPCAN_SetColorLedEnable)(DWORD,BOOL);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetColorLedEnable PCAN_SetColorLedEnable = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetColorLedEnable = (LPPCAN_SetColorLedEnable)GetProcAddress(m_hModule,"PCAN_SetColorLedEnable");
		if(NULL != PCAN_SetColorLedEnable){
			result = PCAN_SetColorLedEnable(m_dwNodeID,enable);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::SetColorLed(DWORD dwColor)
{
	typedef PCANResult (__stdcall * LPPCAN_SetColorLed)(DWORD,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_SetColorLed PCAN_SetColorLed = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_SetColorLed = (LPPCAN_SetColorLed)GetProcAddress(m_hModule,"PCAN_SetColorLed");
		if(NULL != PCAN_SetColorLed){
			result = PCAN_SetColorLed(m_dwNodeID,dwColor);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::WritePDO(DWORD dwRPDOChannel,BYTE *data,DWORD dwLen)
{
	typedef PCANResult (__stdcall * LPPCAN_WritePDO)(DWORD,DWORD,BYTE *,DWORD);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_WritePDO PCAN_WritePDO = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_WritePDO = (LPPCAN_WritePDO)GetProcAddress(m_hModule,"PCAN_WritePDO");
		if(NULL != PCAN_WritePDO){
			result = PCAN_WritePDO(m_dwNodeID,dwRPDOChannel,data,dwLen);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

PCANResult CAxis::ReadPDO(DWORD dwTPDOChannel,BYTE *data,DWORD *pLen)
{
	typedef PCANResult (__stdcall * LPPCAN_ReadPDO)(DWORD,DWORD,BYTE *,DWORD*);
	PCANResult result = PCAN_SUCCESS;
	LPPCAN_ReadPDO PCAN_ReadPDO = NULL;
	if(m_hModule != NULL){
		//获取动态连接库里的函数地址。
		PCAN_ReadPDO = (LPPCAN_ReadPDO)GetProcAddress(m_hModule,"PCAN_ReadPDO");
		if(NULL != PCAN_ReadPDO){
			result = PCAN_ReadPDO(m_dwNodeID,dwTPDOChannel,data,pLen);
		}
	}else{
		result = PCAN_LOADDRIVER_FAIL;
	}
	return result;
}

void CAxis::UpdateControlStatus(BYTE status)
{
	//外部停止1
	if(status&(1<<CS_EXT1)){
	}else{
	}
	//外部停止2
	if(status&(1<<CS_EXT2)){
	}else{
	}
	//堵转标志
	if(status&(1<<CS_STALL)){
	}else{
	}
	//忙标志
	if(status&(1<<CS_BUSY)){
		::ResetEvent(m_hSlaveIdle);
		m_bBusy = 1;
	}else{
		::SetEvent(m_hSlaveIdle);
		m_bBusy = 0;
	}
	//外部停止3
	if(status&(1<<CS_EXT3)){
	}else{
	}
	//PVT模式3下FIFO为空
	if(status&(1<<CS_PVT3_FIFO_EMPTY)){
		m_bPVT3Empty = TRUE;
	}else{
		m_bPVT3Empty = FALSE;
	}
	//PVT模式3下FIFO深度低于下限
	if(status&(1<<CS_PVT3_LOW_THRESHOLD)){
		m_bPVT3Low = TRUE;
	}else{
		m_bPVT3Low = FALSE;
	}
	//PVT模式3下FIFO深度高于上限
	if(status&(1<<CS_PVT3_HIGH_THRESHOLD)){
		m_bPVT3High = TRUE;
	}else{
		m_bPVT3High = FALSE;
	}
}

PCANResult CAxis::WritePVT(int nPosition,int nVelocity,DWORD dwTime)
{
	PCANResult result = PCAN_SUCCESS;
	memcpy(&m_szRPDOData[1][0],&nPosition,sizeof(int));
	memcpy(&m_szRPDOData[1][4],&nVelocity,sizeof(int));
	memcpy(&m_szRPDOData[2][0],&dwTime,sizeof(DWORD));
	m_szRPDOData[2][4] = 2;
	result = WritePDO(RPDO_CH2,m_szRPDOData[1],8);
	if(PCAN_SUCCESS != result){
		return (PCANResult)result;
	}
	result = WritePDO(RPDO_CH3,m_szRPDOData[2],5);
	if(PCAN_SUCCESS != result){
		return (PCANResult)result;
	}
	return result;
}
