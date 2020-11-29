#ifndef _STRUCT_H_
#define _STRUCT_H_
#include "..\inc\define.h"
//显示字符串结构
typedef struct {
	uchar *Str;
}MSGSTRSTRUCT;

//参数提示字符串结构
typedef struct {
	uchar StrId;
}PROMPTSTRUCT;

//主菜单结构
typedef struct {
	uchar MenuStrId; //主菜单名称字符串编号
	uchar ParmNum; //某项主菜单的子参数项数目
	//某项主菜单的第一子参数项对应全体参数的位置{0BASE}
	uchar ParmOffset; 
}MainMenuStruct;

//参数项修改指示：用于参数设置时的指示
//和有效性检查结果
typedef struct {
	uchar CheckValidResult; //有效性检查结果
	//阈值指示; 上限值<->下限值
	//操作指示：数值过大 数值过小 确义保存
	uchar GuideType; 
	uchar MaxGuideStr[20]; //上限阈值指示字符串
	uchar MinGuideStr[20]; //下限阈值指示字符串
	uchar ValidUpperValue; //上限值
	uchar ValidLowerValue; //下限值
}ParmGuideStruct;

//参数结构
typedef struct {
	uchar PasswordUser [4]; //用户密码
	float PulseDampTime; //脉冲阻尼时间
	float ADCDampTime; //电流阻尼时间
	uchar PasswordSys[4]; //系统密码
	uchar Baudrate; //波特率
	uchar Parity; //校验方式
	uchar DeviceNo[2]; //设备号
	float TestIout; //电流输出测试mA
	uchar LoadSettings; //恢复设置
	uchar PasswordTrim[4]; //校准密码
	uchar NewPasswordTrim[4]; //新校准密码
	float TrimZero; //输入零点校准
	float TrimRange; //输入量程校准
	float Trim4mA; //4mA 输出校准
	float Trim20mA; //20mA 输出校准
	uchar SaveSettings; //保存设置
}parmStruct;

//ADC 校准数据结构
typedef struct {
	float Zero; //零点电压
	float Range; //满量程电压
}ADCTrimStruct;

//流量数据结构
typedef struct {
	float Volt; //输入电压
	float Current; //输入电流
	float Freq; //输入频率
}FlowDataStruct;

//键盘输入结构
typedef struct {
	uchar Mode; //参数类型
	//参数中的某一位最大允许值(浮点参数固定为0-9)
	uchar MaxValue; 
	uchar TotalLen; //参数总长度
	uchar DecLen; //浮点参数的小数长度
	float MaxFloat; //浮点参数对应的上限值
	float MinFloat; //浮点参数对应的下限值
	uint Offset; //某项对应的整个参数结构的地址偏移量
	float FloatDataSouce;
	uchar KbdBuff[17];
}KbdInputStruct;

//参数项结构属性
typedef struct {
	uchar Mode; //参数类型
	//参数中的某一位最大允许值(浮点参数固定为0-9)
	uchar MaxValue;
	uchar TotalLen; //参数总长度
	uchar DecLen; //浮点参数的小数长度
	float MaxFloat; //浮点参数对应的上限值
	float MinFloat; //浮点参数对应的下限值
	uint Offset; //某项对应的整个参数结构的地址偏移量
}ParmAttStruct;

//通讯包数据结构
typedef struct {
	uchar Head; //包头
	uchar DeviceNo[2]; //设备地址
	uchar Ins; //指令
	uchar DataBuff[250]; //数据
}CommStruct;

#endif



































	
	
	