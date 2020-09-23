#ifndef _STRUCT_H_
#define _STRUCT_H_
#include "..\inc\define.h"
//��ʾ�ַ����ṹ
typedef struct {
	uchar *Str;
}MSGSTRSTRUCT;

//������ʾ�ַ����ṹ
typedef struct {
	uchar StrId;
}PROMPTSTRUCT;

//���˵��ṹ
typedef struct {
	uchar MenuStrId; //���˵������ַ������
	uchar ParmNum; //ĳ�����˵����Ӳ�������Ŀ
	//ĳ�����˵��ĵ�һ�Ӳ������Ӧȫ�������λ��{0BASE}
	uchar ParmOffset; 
}MainMenuStruct;

//�������޸�ָʾ�����ڲ�������ʱ��ָʾ
//����Ч�Լ����
typedef struct {
	uchar CheckValidResult; //��Ч�Լ����
	//��ֵָʾ; ����ֵ<->����ֵ
	//����ָʾ����ֵ���� ��ֵ��С ȷ�屣��
	uchar GuideType; 
	uchar MaxGuideStr[20]; //������ֵָʾ�ַ���
	uchar MinGuideStr[20]; //������ֵָʾ�ַ���
	uchar ValidUpperValue; //����ֵ
	uchar ValidLowerValue; //����ֵ
}ParmGuideStruct;

//�����ṹ
typedef struct {
	uchar PasswordUser [4]; //�û�����
	float PulseDampTime; //��������ʱ��
	float ADCDampTime; //��������ʱ��
	uchar PasswordSys[4]; //ϵͳ����
	uchar Baudrate; //������
	uchar Parity; //У�鷽ʽ
	uchar DeviceNo[2]; //�豸��
	float TestIout; //�����������mA
	uchar LoadSettings; //�ָ�����
	uchar PasswordTrim[4]; //У׼����
	uchar NewPasswordTrim[4]; //��У׼����
	float TrimZero; //�������У׼
	float TrimRange; //��������У׼
	float Trim4mA; //4mA ���У׼
	float Trim20mA; //20mA ���У׼
	uchar SaveSettings; //��������
}parmStruct;

//ADC У׼���ݽṹ
typedef struct {
	float Zero; //����ѹ
	float Range; //�����̵�ѹ
}ADCTrimStruct;

//�������ݽṹ
typedef struct {
	float Volt; //�����ѹ
	float Current; //�������
	float Freq; //����Ƶ��
}FlowDataStruct;

//��������ṹ
typedef struct {
	uchar Mode; //��������
	//�����е�ĳһλ�������ֵ(��������̶�Ϊ0-9)
	uchar MaxValue; 
	uchar TotalLen; //�����ܳ���
	uchar DecLen; //���������С������
	float MaxFloat; //���������Ӧ������ֵ
	float MinFloat; //���������Ӧ������ֵ
	uint Offset; //ĳ���Ӧ�����������ṹ�ĵ�ַƫ����
	float FloatDataSouce;
	uchar KbdBuff[17];
}KbdInputStruct;

//������ṹ����
typedef struct {
	uchar Mode; //��������
	//�����е�ĳһλ�������ֵ(��������̶�Ϊ0-9)
	uchar MaxValue;
	uchar TotalLen; //�����ܳ���
	uchar DecLen; //���������С������
	float MaxFloat; //���������Ӧ������ֵ
	float MinFloat; //���������Ӧ������ֵ
	uint Offset; //ĳ���Ӧ�����������ṹ�ĵ�ַƫ����
}ParmAttStruct;

//ͨѶ�����ݽṹ
typedef struct {
	uchar Head; //��ͷ
	uchar DeviceNo[2]; //�豸��ַ
	uchar Ins; //ָ��
	uchar DataBuff[250]; //����
}CommStruct;

#endif



































	
	
	