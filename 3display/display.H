/*--------------------------------------------------------------------------
display.H

202009142120
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef LCD_INIT_H
#define LCD_INIT_H

	//sbit rs  = P3^0;

	#if (1) 
		sbit lcd_cs2 = P2^0;
		sbit rst = P2^1; 
		sbit rw  = P2^4; // 默认低，接地
		sbit lcd_en  = P2^6;
		sbit cs1 = P2^7;

		sbit nBLEN = P3^6;
		sbit rs  = P3^7;  //LCD_DI
	#endif
	
	//sbit key = P3^3;
	sbit LED  = P2^2; 
	//LED =1;

	#define DB  P1
	#define uchar unsigned char
	#define uint  unsigned int

	#define S_LINE    0xc0    // 显示起始行 StartLine+0~63
	#define PAGE      0xb8    //  页地址设置 PAGE+0~8  
	#define COL       0x40    //  列地址设置  COL+0~63
	#define DISON     0x3f    // 显示开
	//#define DISOFF    (0x3f-1)  //  显示关    ram被置零
	#define DISOFF    0x3e  //  显示关    ram被置零

	#define cl();  cs1=0;lcd_cs2=1;   // 左选
	//右选  //因模块FM12864A-3的接口（15脚CS1、16脚lcd_cs2）有误	
	#define cr();  cs1=1;lcd_cs2=0;   
	#define ca();  cs1=1;lcd_cs2=1;   //全选15脚CS1、16脚lcd_cs2   
	#define nca();  cs1=0;lcd_cs2=0;   //全不选	  15脚CS1、16脚lcd_cs2   

	
	uchar code fm[];
	uchar code zifu[];
	uchar code qzd[];
	//extern uchar key;
	//extern uchar Line;
	
	void LCD_TEST(void);

#endif

