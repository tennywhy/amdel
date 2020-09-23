#ifndef _comm485_H_
#define _comm485_H_
	// define shot keywords
	#define true 1
	#define false 0
	uint F_Rs485SendStart;
	uint F_Rs485Busy;
	//ÏÔÊ¾×Ö·û´®½á¹¹
typedef struct {
	uchar DeviceNo;
	uchar Ins;
	uchar Head;
	uchar DataBuf[10];
}Comm485;

typedef struct {
	uchar DeviceNo;
	uchar Parity;
}Parm;
typedef struct {
	uchar Freq;
	uchar Current;
}FlowData;

#endif


