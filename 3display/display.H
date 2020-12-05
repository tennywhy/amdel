/*--------------------------------------------------------------------------
display.H

202009142120
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef _display_H_
#define _display_H_

	//sbit lcd_reg_select  = P3^0;

	#if (1) 
		sbit lcd_cs2 = P2^0;
		sbit lcd_reset = P2^1; //lcd_reset
		sbit lcd_rdwr  = P2^4; // 默认低，接地 lcd_rdwr
		sbit lcd_enable  = P2^6; //lcd_enable
		sbit lcd_cs1 = P2^7; //lcd_cs1

		sbit nBLEN = P3^6; //背光开关
		sbit lcd_reg_select  = P3^7;  //LCD_DI lcd_reg_select
	#endif
	
	//sbit key = P3^3;
		sbit LED  = P2^2; 
	//LED =1;

	#define lcd_dataPort  P1 //lcd_dataPort
	//#define uchar unsigned char
	//#define uint  unsigned int

	#define S_LINE    0xc0    // 显示起始行 StartLine+0~63
	#define PAGE      0xb8    //  页地址设置 PAGE+0~8  
	#define PAGEDWHALF 0xb9
	#define COL       0x40    //  列地址设置  COL+0~63
	#define DISON     0x3f    // 显示开
	//#define DISOFF    (0x3f-1)  //  显示关    ram被置零
	#define DISOFF    0x3e  //  显示关    ram被置零

	#define cl()  {lcd_cs1=0;lcd_cs2=1;}   // 左选
	//右选  //因模块FM12864A-3的接口（15脚CS1、16脚lcd_cs2）有误	
	#define cr()  {lcd_cs1=1;lcd_cs2=0;}   
	#define lcd_fullEnable()  {lcd_cs1=1;lcd_cs2=1;}   //全不选15脚CS1、16脚lcd_cs2   
	#define lcd_fullDisable()  {lcd_cs1=0;lcd_cs2=0;}   //全选	  15脚CS1、16脚lcd_cs2   

	
	uchar code fm[];
	uchar code zifu[];
	uchar code qzd[];
	uchar code engChar[];
	uchar code engFull[];
	uchar code engEmpty[];
	uchar code chnFull[];
	uchar code chnEmpty[];
//	extern uchar code ECTAB[];
//	extern uchar code ECTAB[];

	//extern uchar key;
	//extern uchar Line;
	
	void LCD_Clear(void);
	void initPort(void);
	void delaym(unsigned int n);  // 精确MS?
	void CheckBusy(void);
	uchar ReadData(void); // 读数据
	void DisplayOn(void);
	void DisplayOff(void);
	void SendCommand(uchar com); // 发命令
	void SendData(uchar dat);   // 发数据
	void inti(void);
	void ScanKey(void);
	void LCDFill(uchar dat1,uchar dat2); // 全半屏幕显示 
	void PutBmp(uchar *p);
	void Window(void);
	void CPUinti(void);
	void LCDRoll(void);
	void Lcd_init(void);
	void LcdDisplay(menu_disp_t *disp);
	void PutChnChar(uchar *p, uchar pageOffset, uchar charLoca, uchar colOffset, uchar chrType, uchar hightLight);
	//void PutChnChar(uchar *p, uchar pageOffset, uchar chrLoc, uchar colOffset, uchar chrType);
	void SetStcVal(void);
	//void StartMenu(void);
	//void timer(void); interrupt 1   //中断入口


#endif

