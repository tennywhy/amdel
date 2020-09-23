//�����ⲿ���� 24.576Mhz ʹ�ö�ʱ��1����ʽ2���������ʣ�SMOD = 0 ����1
//��ʱ����ʼֵ X=256       - SYSCLK*(SMOD+1)/(BAUDRATE*384)
#include <c8051F000.h>
#include <string.h>
#include "main.h"
//#define uchar  unsigned char
//---------------------------------------------------------------
//����������
//===============================================================
#define BAUDRATE 9600 //������ BPS
#define CLKOUT 24576000 //�ⲿ�����޸�ҲҪ�޸�OSCXCN
#define SMODVAL 0 //SMOD��ֵ���޸�Ҳ�޸�PCONVAL
#define TXVAL (256 - CLKOUT*(SMODVAL+1)/BAUDRATE/384) //��ʱ����ֵ
#define TMAX_LEN 16 //ÿ�η����ַ����ĳ���
#define RMAX_LEN 16 //ÿ�ν����ַ����ĳ���
//---------------------------------------------------------------
//ȫ�ֱ���
//===============================================================
sbit WDI = P0^3; //���Ź��ź�
sbit SendRecv = P2^3; //send 485
uchar rx_data[RMAX_LEN]; //���ջ�����
uchar readHead; //���յ���ͷ��־
uchar readCounts; //�Ѿ���ȡ���ַ�����
uchar readEnd; //���ݽ��ս�����־

uchar tx_data[TMAX_LEN]; //���ͻ����� "@G01tran#"
uchar sendCounts; //�����͵����ݳ���
uchar sendPtr; //��ǰ���ڷ��͵�����ָ��
uchar sendStart; //���ݷ��Ϳ�ʼ��־
uchar sendEnd; //���ݷ��ͽ�����־
//---------------------------------------------------------------
//�Ӻ�������
//===============================================================
void SYSCLK_Init(); //ϵͳʱ�ӳ�ʼ��
void PORT_Init(); //�˿ڳ�ʼ��
void UART_Init(); //����UART0��ʼ��
void Delay(void); 
void UART_ISR(); //�����жϷ������
void ResetWatchDog(); //��λ���Ź�
//----------------------------------------------------------------
//������
//================================================================
void main(void)
{
	EA = 0; //��ȫ���ж�
	//Writing 0xDE followed within 4 clocks 
	//by 0xAD disables the WDT ��ֹ���Ź�
	WDTCN = 0XDE; 
	WDTCN = 0XAD; 
	
	SYSCLK_Init(); //ʱ�ӳ�ʼ��
	PORT_Init(); //�˿ڳ�ʼ��
	UART_Init(); //���ڳ�ʼ��
	ResetWatchDog(); //��λ���Ź�
	readCounts = 0; 
	readEnd =0;
	sendCounts = 0;
	sendPtr = 0;
	sendStart = 0;
	sendEnd = 0;
	EA = 1; //��ȫ���ж�
	ResetWatchDog(); //��λ���Ź�
	tx_data[0] = '@';
	tx_data[1] = '1';
	tx_data[2] = '2';
	tx_data[3] = '3';
	tx_data[4] = '4';
	tx_data[5] = '#';

	SendRecv = 1; //RS485���ڷ���״̬
	while (1)
		{
			ResetWatchDog(); //��λ���Ź�
	/*����ʵ�ֹ��ܣ� ����λ������һ���ַ�������@��ʼ����#������
	��@123#���Ǳ��յ���ԭ������*/
			if (!sendStart)
				{
					sendStart = 1;
					sendEnd = 0;
					sendPtr = 0;
	//�˴�������һ���ַ��Ϳ����ˣ��������һ���ַ���T1=1,
	//�����жϣ������ַ����ж����淢��
					SBUF = tx_data[sendPtr];
				}
			if (readEnd)
				{
	//���յ��������ݰ�����ԭ���ݰ�����
					readEnd = 0;
					sendCounts = readCounts;
					memcpy(tx_data, rx_data, sendCounts);
	//RS485���ڽ���״̬
					SendRecv = 1;
	//�˴���ʱ��Ϊ����485��״̬ת��Ϊ����״̬����Ҫ�ȶ�һ��ʱ��
					Delay();
				}
		}	
}

void Delay(void)
{
	unsigned int i, j;
	for (i=0; i<10000; i++)
		{
			j++;
		}
}

//--------------------------------------------------------------------------
//��������ʵ��
//==========================================================================
//ϵͳʱ�ӳ�ʼ��
void SYSCLK_Init()
{
	int i = 0;
	OSCXCN = 0X67;
	//wait 1ms for initialization
	for (i=0; i<3000; i++);
	while ((OSCXCN & 0X80) == 0);
	OSCICN = 0X08;
	CKCON = 0X10; //T1 ʹ��ϵͳʱ��
}

//�˿ڳ�ʼ��
void PORT_Init()
{
	//P0.0 TX (UART), Open-Drain
	//p0.1 RX (UART), Open-Drain
	//p0.2 T0 (Tmr0), Open-Drain
	XBR0 = 0X04;
	XBR1 = 0X02;
	XBR2 = 0X40;
}

//���ڳ�ʼ��
void UART_Init()
{
	PCON = 0x00; //���ڲ�����ΪSCON�еĴ��ڷ�ʽ����ֵ
	SCON = 0X50; //ѡ�񴮿ڷ�ʽ1�������ʿɱ� SCON0=0101,0000
	TMOD = 0X20; //ѡ��T1,��ʽ2���Զ���װ��8λ������
	TR1 = 0;
	TH1 = 176; //bps = 9600 = (1/32) * 24576000/(256-TH1)
	TL1 = 176;
	ES = 1; //UART0 �жϿ���
	TR1 = 1; //������ʱ��T1
}

//UART0 �жϷ�����򣬽����ַ�
void UART_ISR(void) interrupt 4
{
	uchar rxch;
	if (TI)
		{
			TI = 0;
			sendPtr++;
			if (sendPtr <sendCounts)
				{
					SBUF = tx_data[sendPtr]; //����������һ���ַ�
				}
			else
				{
					sendEnd = 1;
					sendStart = 0;
				}
		}
	if (RI) //�жϱ�־ RI0 = 1 ������������
		{
			RI = 0; //�������
			rxch = SBUF; //������
			if (rxch == '@')
				{ //���ݰ���ʼ��ʶ
					readCounts = 0; //���յ���ͷ�󳤶���0
					readEnd = 0; //��β���յ���ʶ��0
					readHead = 1; //��ͷ���յ���ʶ��1
					rx_data[readCounts] = rxch; //�洢��ͷ
					readCounts++; //������+1
				}
			else if (rxch == '#')
				{ //���ݰ�������ʶ
					if (readHead)
						{ //��ͷ���ձ�ʶ=1ʱ����洢�յ�������
							rx_data[readCounts] = rxch;
							readCounts++;
							readEnd = 1; //��������ʶ��1
							readHead =0; //����ʼ��ʶ��0��������һ�ν���
						}
				}
			else 
				{ //���ݰ�����
					if (readHead)
						{ //��ͷ���ձ�ʶ=1�����������洢�յ�������
							rx_data[readCounts] = rxch;
							readCounts++;
	//�ݴ������ư��������=15����Ϊ���������16����һ���ֽڴ洢��β
	//�������ֵ����ݱ���������ֹ�������
							if (readCounts>=15) readCounts = 15;
						}		
				}
		}
}

void ResetWatchDog()
{
	WDI ^= 1; //zxm-modi ע�����Ź������ź���Ҫ�ߵ͵�ƽ����
}








































