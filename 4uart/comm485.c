//comm485.c
	//485通讯口打包和发送流量数据
#include "main.h"
#include "comm485.h"

void Comm485_SendData(void)
{
	uchar xdata i, send_char;
	uint xdata wait;
	// 清除485发送标志
	F_Rs485SendStart = false;
	if(memcmp(Comm485.DeviceNo, Parm.DeviceNo, 2) != 0) return;
	if(Comm485.Ins == 0x80)	// 0x80	读流量数据
		{
			// 频率(10) + 电流(10)
			Comm485.Head = '=';
			// 频率(10)
			sprintf(&Comm485.DataBuf[0], "%010￡", FlowData.Freq);
			// 电流(10)
			sprintf(&Comm485.DataBuf[10], "*010f",FlowData.Current);
			Comm485.DataBuf[20] = '<';
		}
	else return;
	F_Rs485Busy = 0;
	//set send direction
	SDK_SendRs485();
	SDK_SendRs485();
	SDK_SendRs485();
	SDK_SendRs485();
	wait = 600;
	while(wait) wait--;
	for(i-0; i<250; i++)
	wait = 100;
	while(wait) wait--;
	for(i=0, i<250, i++)
		{
			wait = 100;
			while(wait) wait--;
			F_Rs485Busy = true;
			send_char = *(&Comm485.Head + i);
			ACC = send_char;
			F_Parity = P;
			if(Parm.Parity == 1) TB8 = !F Parity; //奇校验
			if(Parm.Parity == 2) TB8 = F_Parity; //偶校验
			SBUF = send_char;
			while(F_Rs485Busy);
			if(send_char == '<') break;
		}
		wait = 600;
		while(wait) wait--;
		//置接收方向
		SDK_RecvRs485();
		SDK_RecvRs485();
		SDK_RecvRs485();
		SDK_RecvRs485();
}

