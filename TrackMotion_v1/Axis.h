#pragma once

#include <windows.h>
/**************************************宏定义**************************************/
/*跟踪等级*/
#define TRACE_LEVEL0				0
#define TRACE_LEVEL1				1
/*马达状态标志定义*/
#define ES_UVLO						0   //欠压
#define ES_BERR					    1   //B相错误
#define ES_AERR					    2   //A相错误
#define ES_BOC					    3   //B相过流
#define ES_AOC					    4   //A相过流
#define ES_OTS					    5   //过热保护
/*控制器状态标志定义*/
#define CS_EXT1						0	//外部停止1
#define CS_EXT2						1	//外部停止2
#define CS_STALL					2	//堵转标志
#define CS_BUSY						3	//忙标志
#define CS_EXT3						4	//外部停止3
#define CS_PVT3_FIFO_EMPTY			5	//PVT模式3下FIFO为空
#define CS_PVT3_LOW_THRESHOLD		6	//PVT模式3下FIFO深度低于下限
#define CS_PVT3_HIGH_THRESHOLD		7	//PVT模式3下FIFO深度高于上限

/*细分定义*/
#define MS_0						0	//0细分
#define MS_2						2	//2细分
#define MS_4						4	//4细分
#define MS_8						8	//8细分
#define MS_16						16	//16细分
#define MS_32						32	//32细分
#define MS_64						64	//64细分
#define MS_128						128	//128细分
#define MS_256						256	//256细分
/*工作模式定义*/
#define WM_POS						0	//位置模式
#define WM_VELOCITY					1	//速度模式
#define WM_PVT						2	//PVT模式
#define WM_ENC_FOLLOW				3	//编码器跟随模式
/*转动方向定义*/
#define MOTOR_FORWARD				1	//正向转动
#define MOTOR_REVERSE				0	//反向转动
/*外部停止定义*/
#define	EXT_STOP1					0	//外部停止1
#define	EXT_STOP2					1	//外部停止2
#define	EXT_STOP3					4	//外部停止3
/*外部停止触发类型定义*/
#define	EXT_TRIG_FALLING			0	//下降沿触发
#define	EXT_TRIG_RISING				1	//上升沿触发

/*PVT模式定义*/
#define	PVT_MODE1					0	//PVT模式1,单次模式
#define	PVT_MODE2					1	//PVT模式2,循环模式
#define	PVT_MODE3					2	//PVT模式3,无限FIFO模式

/*GPIO定义*/
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
/*GPIO方向*/
#define GPIO_DIR_IN					0
#define GPIO_DIR_OUT				1
/*GPIO输入端口配置*/
#define GPIO_IN_FLOATING			0
#define GPIO_IN_IPU					1
#define GPIO_IN_IPD					2
#define GPIO_IN_AIN					3
/*GPIO输出端口配置*/
#define GPIO_OUT_OD					0
#define GPIO_OUT_PP					1

/*颜色配置*/
#ifndef RGB
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif

/*RPDO通道配置*/
#define RPDO_CH1					0 //接收PDO通道1
#define RPDO_CH2					1 //接收PDO通道2
#define RPDO_CH3					2 //接收PDO通道3
#define RPDO_CH4					3 //接收PDO通道4

/*TPDO通道配置*/
#define TPDO_CH1					0 //发送PDO通道1
#define TPDO_CH2					1 //发送PDO通道2
#define TPDO_CH3					2 //发送PDO通道3
#define TPDO_CH4					3 //发送PDO通道4

/*PP/PV模式控制字位定义*/
//当值由"0"转换至"1"时，执行运行任务。
#define CW_NEW_TARGET		(1<<4)
//当该位被设为"1"时，将立即执行由位4触发的运行任务。若该位被设为"0"，将先完成正在执行的运行任务，然后才启动下个运行任务。
#define CW_EXEC_IMM			(1<<5) 
//当值设为"0"时，目标位置 (607Ah) 是绝对位置，当值设为"1"时，目标位置是基于当前位置的相对位置
#define CW_ABS				(1<<6)
//当该位的值由"1"变为"0"时，电机将以预设的启动斜坡加速至目标速度。当该位的值由"0"变为"1"时，电机将减速并停止运动。
#define CW_HALT				(1<<8)
//当该位被设定时，将在到达首个目标位置后改变速度。这就是说，在到达首个目标前不会执行制动，因为电机不应停在该位置上。
#define CW_BRAKE_NONE		(1<<9)

/*PP/PV模式状态字位定义*/
//当最后的目标已到达，该位将被设为"1"。
#define SW_TARGET_ARRIVED	(1<<10)
//该位确认收到有效的新目标点。该位将与Controlword中的位"New set-point"同步设定和复位。
#define SW_TARGET_ACK		(1<<12)

/**************************************类型定义**************************************/
/*适配器型号*/
typedef enum{
	LANMA_A1PLUS = 0,//蓝马电子A1+
	LEDIA = 1,//乐的USB-CAN
	YL9100 = 2,//YL9100
	IXXAT = 3,//IXXAT
	GC_USBCAN_I = 4,//广成USBCAN-I
	ZLG_USBCAN_I = 5,//周立功USBCAN-I
	ZLG_USBCAN_E_U = 6,//周立功USBCAN-E-U
	ZLG_CANET_TCPC = 7,//周立功CANET-TCP客户端
	CX_CANALYST_II	= 8,//创芯CANalyst-II，我们用的是这个
	ZLG_CANCOM_100IE = 9,//周立功CANCOM-100IE
}ADAPT_TYPE_T;

/*PUSI CAN设备型号*/
typedef enum{
	PMC007C3S = 0,
	PMC007C6S = 1,
	PMC007C3SE = 2,
	PMC007C6SE = 3, //我们用的是这个
}PCAN_TYPE_T;

typedef enum{
	BR_10KBPS = 0,
	BR_20KBPS = 1,
	BR_50KBPS = 2,
	BR_100KBPS = 3,
	BR_125KBPS = 4,  //一般用125？
	BR_250KBPS = 5,
	BR_500KBPS = 6,
	BR_800KBPS = 7,
	BR_1000KBPS = 8,
}BAUDRATE_T;

typedef enum
{
	PCAN_SUCCESS = 0, /*操作成功*/
	PCAN_GENERNAL_ERR = 1, /*通用错误*/
	PCAN_LOADDRIVER_FAIL = 2, /* 装载驱动失败 */
	PCAN_OPEN_FAIL = 3,  /*打开适配器失败*/
	PCAN_READSDO_FAIL = 4, /*读SDO失败*/
	PCAN_READSDO_TIMEOUT = 5, /*读SDO超时*/
	PCAN_WRITESDO_FAIL = 6, /*写SDO失败*/
	PCAN_WRITESDO_TIMEOUT = 7, /*写SDO超时*/	
	PCAN_NOIDLE_SDO_CLIENT = 8,/*SDO客户端没有可用的通道*/
	PCAN_WRITEPDO_FAIL = 9,/*写PDO失败*/
	PCAN_NO_SUPPORT_TCP_CONNECT = 10,/*不支持TCP连接*/
	PCAN_NO_SUPPORT_SP_CONNECT = 11,/*不支持串口连接*/
	PCAN_SLAVE_NOT_ONLINE = 12,/*节点不在线*/
}PCANResult;

// 定义函数指针
typedef PCANResult (__stdcall * LPPCAN_SLAVECHANGECB)(DWORD dwNodeID,BOOL bOnline);
typedef PCANResult (__stdcall * LPPCAN_TRACECB)(char* szTrace);
typedef PCANResult (__stdcall * LPPCAN_TPDOCB)(DWORD dwNodeID,DWORD dwTPDOChannel,BYTE* pTPDOData,DWORD dwLen);

class CAxis
{
public:
	CAxis(void); //构造函数
	CAxis(DWORD dwNodeID);
	~CAxis(void);//析构函数
//动态库接口函数
public:
/*********************通用控制函数*********************/
	/*设置回调函数*/
	static PCANResult SetEventCallback(LPPCAN_SLAVECHANGECB funcSlaveChange, LPPCAN_TRACECB funcTraceCallback, LPPCAN_TPDOCB funcTPDOCallback);
	/*初始化*/
	static PCANResult Init(ADAPT_TYPE_T adaptType, PCAN_TYPE_T devType, DWORD dwTraceLevel);
	/*设置TCP通信参数*/
	static PCANResult SetTCPClient(char *szIPAddr,DWORD dwPort);
	/*设置串口参数*/
	static PCANResult SetSerialPort(DWORD dwPort,DWORD dwBaud);
	/*打开端口*/
	static PCANResult OpenPort(BAUDRATE_T baudrate);
	/*关闭端口*/
	static PCANResult ClosePort();
	
/*********************NMT节点管理*********************/
	/*节点上线状态*/
	PCANResult IsSlaveOnline(BOOL *pOnline);
	/*启动节点*/
	PCANResult StartNode();
	/*停止节点*/
	PCANResult StopNode();
	/*复位节点*/
	PCANResult ResetNode();
	/*复位通信*/
	PCANResult ResetCommunication();
	/*进入预操作状态*/
	PCANResult EnterPreoperational();
/*********************系统控制*********************/
	/*保存对象字典参数*/
	PCANResult SaveObjectDict();
/*********************基本马达运动控制*********************/
	/*获取马达状态*/
	PCANResult GetMotorStatus(DWORD* pMotorStatus);
	/*获取控制状态*/
	PCANResult GetControlStatus(DWORD* pControlStatus);
	/*获取电机使能*/
	PCANResult GetMotorEnable(BOOL *pMotorEnable);
	/*设置电机使能*/
	PCANResult SetMotorEnable(BOOL bMotorEnable);
	/*获取峰值电流*/
	PCANResult GetPeakCurrent(DWORD *pPeakCurrent);
	/*设置峰值电流*/
	PCANResult SetPeakCurrent(DWORD dwPeakCurrent);
	/*获取电流衰减*/
	PCANResult GetCurrentDecay(DWORD *pCurrentDecay);
	/*设置电流衰减*/
	PCANResult SetCurrentDecay(DWORD dwCurrentDecay);
	/*获取细分数*/
	PCANResult GetMicroStep(DWORD *pMicroStep);
	/*设置细分数*/
	PCANResult SetMicroStep(DWORD dwMicroStep);
	/*获取工作模式*/
	PCANResult GetWorkMode(DWORD *pWorkMode);
	/*设置工作模式*/
	PCANResult SetWorkMode(DWORD dwWorkMode);
	/*获取转动方向*/
	PCANResult GetDir(DWORD *pDir);
	/*设置转动方向*/
	PCANResult SetDir(DWORD dir);
	/*获取启动速度*/
	PCANResult GetStartSpeed(DWORD *pStartSpeed);
	/*设置启动速度*/
	PCANResult SetStartSpeed(DWORD dwStartSpeed);
	/*获取停止速度*/
	PCANResult GetStopSpeed(DWORD *pStopSpeed);
	/*设置停止速度*/
	PCANResult SetStopSpeed(DWORD dwStopSpeed);
	/*获取加速度系数*/
	PCANResult GetAccel(DWORD *pAccel);
	/*设置加速度系数*/
	PCANResult SetAccel(DWORD dwAccel);
	/*获取减速度系数*/
	PCANResult GetDecel(DWORD *pDecel);
	/*设置减速度系数*/
	PCANResult SetDecel(DWORD dwDecel);
	/*获取最大速度*/
	PCANResult GetMaxSpeed(int *pMaxSpeed);
	/*设置最大速度*/
	PCANResult SetMaxSpeed(int nMaxSpeed);
	/*PP/PV模式设置目标位置*/
	PCANResult GetTargetPos(int *pTargetPos);
	/*PP/PV模式设置目标位置*/
	PCANResult SetTargetPos(int nTargetPos);
	/*获取马达位置*/
	PCANResult GetMotorPos(int *pMotorPos);
	/*设置马达位置*/
	PCANResult SetMotorPos(int nMotorPos);
	/*相对位置步进*/
	PCANResult StartRelStep(DWORD dwStepNum);
	/*绝对位置步进*/
	PCANResult StartAbsStep(int nAbsPos);
	/*终止步进*/
	PCANResult AbortStep();
/*********************传感器输入*********************/
	/*获取外部紧急停止使能*/
	PCANResult GetExtStopEnable(DWORD *pExtStopEnable);
	/*设置外部紧急停止使能*/
	PCANResult SetExtStopEnable(DWORD dwExtStopEnable);
	/*获取外部紧急停止触发方式*/
	PCANResult GetExtStopTrigger(DWORD *pExtStopTrigger);
	/*设置外部紧急停止触发方式*/
	PCANResult SetExtStopTrigger(DWORD dwExtStopTrigger);
	/*获取外部紧急停止去抖延时*/
	PCANResult GetDebounceDelay(DWORD *pDebounceDelay);
	/*设置外部紧急停止去抖延时*/
	PCANResult SetDebounceDelay(DWORD dwDebounceDelay);
	/*清除外部紧急停止标志*/
	PCANResult ClearExtStopFlag(DWORD dwExtStopFlag);
/*********************PVT运动控制*********************/
	/*设置组ID*/
	PCANResult SetGroupID(DWORD dwGroupID);
	/*设置PVT模式*/
	PCANResult SetPVTMode(DWORD dwPVTMode);
	/*设置最大PVT数据个数*/
	PCANResult SetMaxPVTNum(DWORD dwMaxPVTNum);
	/*设置PVT1参数*/
	PCANResult SetPVT1Para(DWORD dwStartIndex,DWORD dwEndIndex);
	/*设置PVT2参数*/
	PCANResult SetPVT2Para(DWORD dwAccStartIndex,DWORD dwAccEndIndex,DWORD dwLoopStartIndex,\
		DWORD dwLoopEndIndex,DWORD dwLoopCount,DWORD dwDecStartIndex,DWORD dwDecEndIndex);
	/*设置PVT3参数*/
	PCANResult SetPVT3Para(DWORD dwLowThreshold,DWORD dwHighThreshold);	
	/*SDO写PVT参数*/
	PCANResult SDOWritePVT(int nPosition, int nVelocity, DWORD dwTime);
	/*启动PVT步进*/
	static PCANResult StartPVTStep(DWORD dwGroupID);
	/*停止PVT步进*/
	static PCANResult StopPVTStep(DWORD dwGroupID);
/*********************PV运动控制*********************/
	/*写PV参数*/
	PCANResult PCAN_SetSyncPosPara(int nPosition,int nVelocity);
	/*启动PV步进*/
	static PCANResult PCAN_StartSyncStep(DWORD dwGroupID);
/*********************端口控制*********************/
	/*获取GPIO方向*/
	PCANResult GetGPIODir(DWORD *pGPIODir);
	/*设置GPIO方向*/
	PCANResult SetGPIODir(DWORD dwGPIODir);
	/*获取GPIO配置*/
	PCANResult GetGPIOConfig(DWORD *pGPIOConfig);
	/*设置GPIO配置*/
	PCANResult SetGPIOConfig(DWORD dwGPIOConfig);
	/*获取GPIO值*/
	PCANResult GetGPIOValue(DWORD *pGPIOValue);
	/*设置GPIO值*/
	PCANResult SetGPIOValue(DWORD dwGPIOValue);
/*********************幻彩灯控制*********************/
	/*幻彩灯参数*/
	PCANResult SetColorLedPara(DWORD dwFreq,DWORD dwDutyCycle0,DWORD dwDutyCycle1);
	/*幻彩灯使能*/
	PCANResult SetColorLedEnable(BOOL enable);
	/*幻彩灯颜色设置*/
	PCANResult SetColorLed(DWORD dwColor);
/*********************PDO控制接口*********************/
	/*写PDO*/
	PCANResult WritePDO(DWORD dwRPDOChannel,BYTE *data,DWORD dwLen);
	/*读PDO*/
	PCANResult ReadPDO(DWORD dwTPDOChannel,BYTE *data,DWORD *pLen);
	/*更新状态*/
	void UpdateControlStatus(BYTE status);
	PCANResult WritePVT(int nPosition,int nVelocity,DWORD dwTime);
private:
	static HMODULE m_hModule; //动态库模块句柄
	static DWORD m_dwInstanceCount; //轴的实例计数
	static LPPCAN_SLAVECHANGECB m_pfnSlaveChangeCallback; //从站状态改变回调函数
	static LPPCAN_TRACECB m_pfnTraceCallback; //从站的跟踪信息
	static LPPCAN_TPDOCB m_pfnTPDOCallback; //从站的TPDO回调信息
	BYTE m_szTPDOData[4][8]; //TPDO 通道数据
	BYTE m_szRPDOData[4][8]; //RPDO 通道数据
public:
	DWORD m_dwNodeID;  //节点ID
	DWORD m_dwGroupID; //组ID
	BOOL m_bSlaveOnline; //从站在线状态？
	BOOL m_bBusy; //忙状态
	BOOL m_bPVT3Low; //PVT3 FIFO下限
	BOOL m_bPVT3High; //PVT3 FIFO上限
	BOOL m_bPVT3Empty; //PVT3 FIFO空
	HANDLE m_hSlaveOnline; //从站上线事件
	HANDLE m_hSlaveIdle; //从站空闲状态

};

