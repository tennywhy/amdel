//采用外部晶振 24.576Mhz 使用定时器1，方式2产生波特率，SMOD = 0 或者1
//定时器初始值 X=256       - SYSCLK*(SMOD+1)/(BAUDRATE*384)
#include <c8051F000.h>
#include <string.h>
#include "main.h"
//#define uchar  unsigned char
//---------------------------------------------------------------
//参数设置区
//===============================================================
#define BAUDRATE 9600 //波特率 BPS
#define CLKOUT 24576000 //外部晶振，修改也要修改OSCXCN
#define SMODVAL 0 //SMOD的值，修改也修改PCONVAL
#define TXVAL (256 - CLKOUT*(SMODVAL+1)/BAUDRATE/384) //定时器初值
#define TMAX_LEN 16 //每次发送字符串的长度
#define RMAX_LEN 16 //每次接收字符串的长度
//---------------------------------------------------------------
//全局变量
//===============================================================
sbit WDI = P0^3; //看门狗信号
sbit SendRecv = P2^3; //send 485
uchar rx_data[RMAX_LEN]; //接收缓冲区
uchar readHead; //接收到包头标志
uchar readCounts; //已经读取的字符个数
uchar readEnd; //数据接收结束标志

uchar tx_data[TMAX_LEN]; //发送缓冲区 "@G01tran#"
uchar sendCounts; //待发送的数据长度
uchar sendPtr; //当前正在发送的数据指针
uchar sendStart; //数据发送开始标志
uchar sendEnd; //数据发送结束标志
//---------------------------------------------------------------
//子函数声明
//===============================================================
void SYSCLK_Init(); //系统时钟初始化
void PORT_Init(); //端口初始化
void UART_Init(); //串口UART0初始化
void Delay(void); 
void UART_ISR(); //串口中断服务程序
void ResetWatchDog(); //复位看门狗
//----------------------------------------------------------------
//主函数
//================================================================
void main(void)
{
	EA = 0; //关全局中断
	//Writing 0xDE followed within 4 clocks 
	//by 0xAD disables the WDT 禁止看门狗
	WDTCN = 0XDE; 
	WDTCN = 0XAD; 
	
	SYSCLK_Init(); //时钟初始化
	PORT_Init(); //端口初始化
	UART_Init(); //串口初始化
	ResetWatchDog(); //复位看门狗
	readCounts = 0; 
	readEnd =0;
	sendCounts = 0;
	sendPtr = 0;
	sendStart = 0;
	sendEnd = 0;
	EA = 1; //开全局中断
	ResetWatchDog(); //复位看门狗
	tx_data[0] = '@';
	tx_data[1] = '1';
	tx_data[2] = '2';
	tx_data[3] = '3';
	tx_data[4] = '4';
	tx_data[5] = '#';

	SendRecv = 1; //RS485处于发送状态
	while (1)
		{
			ResetWatchDog(); //复位看门狗
	/*测试实现功能： 从上位机发送一个字符串，以@开始，以#结束，
	如@123#，仪表收到后原包返回*/
			if (!sendStart)
				{
					sendStart = 1;
					sendEnd = 0;
					sendPtr = 0;
	//此处仅发送一个字符就可以了，发送完第一个字符后，T1=1,
	//启动中断，后续字符在中断里面发送
					SBUF = tx_data[sendPtr];
				}
			if (readEnd)
				{
	//接收到完整数据包，将原数据包返回
					readEnd = 0;
					sendCounts = readCounts;
					memcpy(tx_data, rx_data, sendCounts);
	//RS485处于接收状态
					SendRecv = 1;
	//此处延时是为了让485的状态转换为发送状态后，需要稳定一段时间
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
//函数具体实现
//==========================================================================
//系统时钟初始化
void SYSCLK_Init()
{
	int i = 0;
	OSCXCN = 0X67;
	//wait 1ms for initialization
	for (i=0; i<3000; i++);
	while ((OSCXCN & 0X80) == 0);
	OSCICN = 0X08;
	CKCON = 0X10; //T1 使用系统时钟
}

//端口初始化
void PORT_Init()
{
	//P0.0 TX (UART), Open-Drain
	//p0.1 RX (UART), Open-Drain
	//p0.2 T0 (Tmr0), Open-Drain
	XBR0 = 0X04;
	XBR1 = 0X02;
	XBR2 = 0X40;
}

//串口初始化
void UART_Init()
{
	PCON = 0x00; //串口波特率为SCON中的串口方式定义值
	SCON = 0X50; //选择串口方式1，波特率可变 SCON0=0101,0000
	TMOD = 0X20; //选择T1,方式2，自动再装入8位计数器
	TR1 = 0;
	TH1 = 176; //bps = 9600 = (1/32) * 24576000/(256-TH1)
	TL1 = 176;
	ES = 1; //UART0 中断开启
	TR1 = 1; //启动定时器T1
}

//UART0 中断服务程序，接收字符
void UART_ISR(void) interrupt 4
{
	uchar rxch;
	if (TI)
		{
			TI = 0;
			sendPtr++;
			if (sendPtr <sendCounts)
				{
					SBUF = tx_data[sendPtr]; //继续发送下一个字符
				}
			else
				{
					sendEnd = 1;
					sendStart = 0;
				}
		}
	if (RI) //中断标志 RI0 = 1 数据完整接收
		{
			RI = 0; //软件清零
			rxch = SBUF; //读缓冲
			if (rxch == '@')
				{ //数据包开始标识
					readCounts = 0; //接收到包头后长度清0
					readEnd = 0; //包尾接收到标识清0
					readHead = 1; //包头接收到标识置1
					rx_data[readCounts] = rxch; //存储包头
					readCounts++; //包长度+1
				}
			else if (rxch == '#')
				{ //数据包结束标识
					if (readHead)
						{ //包头接收标识=1时允许存储收到的数据
							rx_data[readCounts] = rxch;
							readCounts++;
							readEnd = 1; //包结束标识置1
							readHead =0; //包起始标识清0，便于下一次接收
						}
				}
			else 
				{ //数据包内容
					if (readHead)
						{ //包头接收标识=1的情况下允许存储收到的数据
							rx_data[readCounts] = rxch;
							readCounts++;
	//容错处理，限制包长度最大=15，因为级冲区最大16，留一个字节存储包尾
	//超出部分的数据被舍弃，防止缓冲溢出
							if (readCounts>=15) readCounts = 15;
						}		
				}
		}
}

void ResetWatchDog()
{
	WDI ^= 1; //zxm-modi 注：看门狗激活信号需要高低电平交替
}








































