
//#include <reg52.h>
#include "..\1head\0common.h"
#include "display.H"
//#include "struct.h"
#include "..\5msgCalc\msgCalc.h"
#include "defineSTC.h"
#include "dsplMenu.h"





//显示字符串结构
//typedef struct stringSet{
//struct stringSet{
//	uchar strMenu[4][16];
//
//}aallStringSet[]={{1,2,3},{1,2,3},{1,2,3},};


uchar key = 1;
uchar Line = 0;
uchar GchrLocation=0;


void initPort()
{
//	PRT1CF    = 0xFF;
//    PRT2CF    = 0xFF;
//    PRT3CF    = 0xFF;
    //XBR2      = 0x40;
    _nop_();
}

void delaym(unsigned int n)
{
	unsigned int i,j;
	for(j=n;j>0;j--)
	for(i=112;i>0;i--);
}                         /////// 精确MS?
void CheckBusy()
{
	delaym(1);
}

uchar ReadData()      ////////// 读数据
{
	uchar dat;
	lcd_reg_select  =  1;
	lcd_rdwr  =  1;
	lcd_dataPort  =  0xff;
	lcd_enable  =  1;
	_nop_();
	dat = lcd_dataPort;
	lcd_enable  =  0;
	_nop_();
	return dat;
}

void DisplayOn()
{
	SendCommand(DISON);
}

void DisplayOff()
{
	LCDFill(0x00,0x00);
	SendCommand(DISOFF);
}

void SendCommand_a(uchar com)     ///// 发命令
{
	SendData(com);
}

void SendCommand(uchar com)     ///// 发命令
{
	CheckBusy();
	lcd_dataPort  =  com;
	lcd_reg_select  =  0;
	lcd_rdwr  =  0;
	lcd_enable  =  1;
	_nop_();
	lcd_enable  =  0;
	_nop_();
}


void SendData(uchar dat)     ///// 发数据
{
	CheckBusy();
	lcd_dataPort  =  dat;
	lcd_reg_select  =  1;
	lcd_rdwr  =  0;
	lcd_enable  =  1;
	_nop_();
	lcd_enable  =  0;
	_nop_();
}

void inti()
{
	lcd_fullEnable();
	SendCommand(S_LINE);
	SendCommand(COL);	
	SendCommand(PAGE);
	SendCommand(DISOFF);
	SendCommand(DISON);
}

void ScanKey()
{
	while(key)
	{
		delaym(50);
	 };
	while(!key)
	{
		delaym(20);
	}
}

void LCDFill(uchar dat1,dat2)    /// 全半屏幕显示 /////
{
	uchar i,j;	
	
	lcd_fullEnable();  //lcd_fullEnable
	SendCommand(COL);
	SendCommand(PAGE);
	for(j=1;j<9;j++)  //j=1;j<9
		{
		for(i=0;i<64;i++)
			{
			SendData(dat1);  //dat1
			SendData(dat2);  //dat2
			//SendData(0xaa);  //dat2
			};
		SendCommand(PAGE+j);
		};
	lcd_fullDisable();
}


//显示一个字符，（显示内容，所在行，开始位置(字符），偏移，类型(2汉字，1字符），是否高亮（1高亮））
void PutChnChar(uchar *p, uchar pageOffset, uchar charLoca, uchar colOffset, uchar chrType, uchar hightLight)  //显示汉字
{
	//uchar pageOffset = 4;
	//extern GchrLocation;	

	
	uchar chrCol=0, chrPag=0;
	uchar i=0, j=0, rightScreen=FALSE;
	uchar chrLen=0, cross64=1;
	//chrType=2;
//	uchar k=0;
//	k=GchrLocation;
//	printf("putchar %d ",(short) k);
		//SendCommand(COL);
		//chrLen = sizeof(p);
		//charLoca=GchrLocation+colOffset;
		chrPag = PAGE + pageOffset;
		//chrCol = colOffset + charLoca*8;
		chrCol = charLoca*8+colOffset;;
		//lcd_fullEnable();
		if ( chrCol >= 64) 
			{
				chrCol = chrCol-64;
				//rightScreen =TRUE;
				//delaym(1);
				cr();
			}	
		else 
			{
				cl();
			}
		SendCommand(COL+chrCol);
		SendCommand(chrPag);
		//显示字符上半部分
		for(i=0;i<(chrType*8);i++)
			{
				if((chrCol+i>=64) && (cross64 ==1))
					{				
						cr();
						SendCommand(COL+0);
						SendCommand(chrPag);
						//delaym(5);
						cross64=0;
					}	
				if(hightLight==0)
					{
						SendData(*(p+i));
					}
				else
					{
						SendData(0xff-*(p+i));
					}
			};
		//显示字符下半部分
		
		if ( cross64==0) 
			{
				cross64=1;
				cl();
			}
		SendCommand(COL+chrCol);
		SendCommand(chrPag+1);		
		for(i=(chrType*8);i<(chrType*8*2);i++)
			{
				if((chrCol+i-chrType*8>=64) && (cross64 ==1))
					{
						cr();
						SendCommand(COL+0);
						SendCommand(chrPag+1);	
						cross64=0;
						//printf("goes corss64\n");
					}	
				if(hightLight==0)
					{
						SendData(*(p+i));
					}
				else
					{
						SendData(0xff-*(p+i));
					}
			};
}


void PutBmp(uchar *p)
{
	uchar i,j;
	uint  k=0;
	
	for(j=0;j<2;j++)
		{
		cl();
		SendCommand(COL+16);
		SendCommand(PAGE);
		//lcd_fullEnable();
		for(i=0;i<16;i++)
			{
			SendData(*(p+k));
			k++;
			};
			j++;
			//DebugStop();
		SendCommand(COL+16);
		SendCommand(PAGE+j);
		for(i=0;i<16;i++)
			{
			SendData(*(p+k));
			k++;
			};		
//		cr();
//		for(i=0;i<64;i++)
//			{
//			//SendData(*(p+k));
//			SendData(0x00);
//			k++;
//			};
		lcd_fullDisable();
		};
}

void Lcd_init()
{
	
	delaym(10);
	initPort();
	inti();
	nBLEN = 0; //打开背光
	//printf("lcd start 333");
	//DebugStop();
}
void LcdDisplay()
{

	uchar tempa = 0;
	uchar rowdat, coldat; //行数据，列数据
	//uchar *chr;
	//printf("lcdDIS start");


	DisplayLogic();


	//LCD_Clear();
//	ParamSetLogic();

//	StaticDisp();
//	rowdat++;

//	PutEngChar(chr, 2,4,0);
	
//	for(rowdat=0; rowdat<26; rowdat++) 
//		{
//			StaticDisp(rowdat*4);
//			delaym(5000);
//		}

}

void timer() interrupt 1            ///////////中断入口
{
	Line++;
	if(Line>63)
		{
		Line=0;
		};
	SendCommand(S_LINE+Line);
	TH0=0x00;
	TL0=0xb0;
}

void LCD_Clear() 
{
	uchar i,j;	
	//lcd_fullEnable();  //lcd_fullEnable
	lcd_fullEnable();
	//lcd_fullDisable();
	
	for(j=0;j<8;j++)  //j=1;j<9
		{
			SendCommand(COL);
			SendCommand(PAGE+j);	
			CheckBusy();
			for(i=0;i<64;i++)
				{
				SendData(0x00);  //dat1
				//delaym(100);
				//printf("page is %d %d \n", (short) j, (short) i);
				}
			CheckBusy();
		}
		//DebugStop();
	lcd_fullDisable();
	//DebugStop();
}


